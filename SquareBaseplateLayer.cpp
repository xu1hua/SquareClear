//
//
//
//	Created by xuhua on 16/5/10
//  游戏的基板类，将方块置于基板的空格中
//
//

#include "SquareBaseplateLayer.h"
#include "Square.h"
USING_NS_CC;
int baselist[] = 
{
	1, 1, 1, 1, 1, 1,
	1, 1, 0, 1, 1, 1,
	1, 1, 0, 1, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
};

SquareBaseplateLayer* SquareBaseplateLayer::s_pSquareBaseplateLayer = NULL;
SquareBaseplateLayer::SquareBaseplateLayer()
:_baseSize(BaseSize(1,1))
,_squareSize(Vec2(1,1))
{
	if (s_pSquareBaseplateLayer)
	{
		assert(0);
	}
	s_pSquareBaseplateLayer = this;
	m_baseSquareList = new std::vector < BaseSquare >();
}

SquareBaseplateLayer::~SquareBaseplateLayer()
{
	for (auto sq : *m_baseSquareList)
	{
		delete sq.pSquare;
	}
	m_baseSquareList->clear();
	delete m_baseSquareList;
	s_pSquareBaseplateLayer = NULL;
}

bool SquareBaseplateLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
    
    m_drawNode = DrawNode::create();
    addChild(m_drawNode, 1);
    
	setBaseSize(BaseSize(6,6));
	for (int i = 0; i <= getBaseSize().width * getBaseSize().height; i++)
	{
		switch (baselist[i])
		{
		case 0:
			//上下翻转，因为gl坐标原点在左下。
			m_baseSquareList->push_back(BaseSquare(SquareBaseplateState::SQBS_EMPTY,
				new Square(i % getBaseSize().width, getBaseSize().height - 1 - i / getBaseSize().height, Square::SC_RED)
				));
			break;
		case 1:
			//上下翻转，因为gl坐标原点在左下。
			m_baseSquareList->push_back(BaseSquare(SquareBaseplateState::SQBS_MAP,
				new Square(i % getBaseSize().width, getBaseSize().height - 1 - i / getBaseSize().height, Square::SC_RED)
				));
			break;
		default:
			//上下翻转，因为gl坐标原点在左下。
			m_baseSquareList->push_back(BaseSquare(SquareBaseplateState::SQBS_EMPTY,
				new Square(i % getBaseSize().width, getBaseSize().height - 1 - i / getBaseSize().height, Square::SC_RED)
				));
			break;
		}
	}
    
    
    return true;
}

void SquareBaseplateLayer::drawBasesplate(Vec2 squareSize)
{
	setSquareSize(squareSize);
	m_drawNode->clear();
    for(auto sq : *m_baseSquareList)
    {//todo 将绘制方法放在Square类中实现，加入描边功能
  //      Vec2 _origin =(Vec2(squareSize.x * sq->getIndexX(), squareSize.y * sq->getIndexY()));
		//Vec2 _dest = (Vec2(squareSize.x * (sq->getIndexX() + 1), squareSize.y * (sq->getIndexY() + 1)));
  //      
  //      m_drawNode->drawSolidRect(_origin, _dest, sq->getColor4F());
		if (sq.pSquare)
		{
			switch (sq.squareState)
			{
			case SQBS_EMPTY:
				break;
			case SQBS_MAP:
				sq.pSquare->drawSquare(m_drawNode, squareSize);
				break;
			case SQBS_FRAME:
				sq.pSquare->drawFrame(m_drawNode, squareSize,Color4F::YELLOW);
				break;
			case SQBS_SQUARE:
				break;
			default:
				break;
			}
			
		}
		
    }
}

void SquareBaseplateLayer::drawBasesplate()
{
	drawBasesplate(getSquareSize());
}

int SquareBaseplateLayer::checkSquareIsEmptyOrFrame(cocos2d::Vec2 point)
{
	Vec2 pos =  convertToNodeSpace(point);
	if (pos.x < 0 || pos.x > getBaseSize().width * getSquareSize().x)
	{
		return -1;
	}
	if (pos.y < 0 || pos.y > getBaseSize().height * getSquareSize().y)
	{
		return -1;
	}

	int _indexX = (int)(pos.x / getSquareSize().x);
	int _indexY = getBaseSize().height - 1 - (int)(pos.y / getSquareSize().y);
	int _index = _indexY * getBaseSize().width + _indexX;
	if (_index >= m_baseSquareList->size())
	{
		return -1;
	}
	if ((*m_baseSquareList)[_index].squareState == SquareBaseplateState::SQBS_EMPTY
		|| (*m_baseSquareList)[_index].squareState == SquareBaseplateState::SQBS_FRAME
		)
	{
		return _index;
	}
	return -1;
}

void SquareBaseplateLayer::clearFrameSquare()
{
	for (auto &basesquare:*m_baseSquareList)
	{
		if (basesquare.squareState == SquareBaseplateState::SQBS_FRAME)
		{
			basesquare.squareState = SquareBaseplateState::SQBS_EMPTY;
		}
	}
}

void SquareBaseplateLayer::PlaceSquare(int index)
{
	if (index >= m_baseSquareList->size())
	{
		assert(0);
	}
	if ((*m_baseSquareList)[index].squareState == SquareBaseplateState::SQBS_EMPTY || (*m_baseSquareList)[index].squareState == SquareBaseplateState::SQBS_FRAME)
	{
		(*m_baseSquareList)[index].squareState = SquareBaseplateState::SQBS_SQUARE;
	}
	else
	{
		assert(0);
	}
	
}

void SquareBaseplateLayer::setFrame(int index)
{
	if (index >= m_baseSquareList->size())
	{
		assert(0);
	}
	if ((*m_baseSquareList)[index].squareState == SquareBaseplateState::SQBS_EMPTY || (*m_baseSquareList)[index].squareState == SquareBaseplateState::SQBS_FRAME)
	{
		(*m_baseSquareList)[index].squareState = SquareBaseplateState::SQBS_FRAME;
	}
	else
	{
		assert(0);
	}
}

cocos2d::Vec2 SquareBaseplateLayer::getWorldPos(int index)
{
	if (index >= m_baseSquareList->size())
	{
		assert(0);
	}
	Vec2 squarePos = Vec2(index%getBaseSize().width * getSquareSize().x, (getBaseSize().height - 1 - index/getBaseSize().height) * getSquareSize().y);
	Vec2 worldPos = getParent()->convertToWorldSpace(getPosition() + squarePos);

	return worldPos;
}
