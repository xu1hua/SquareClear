//
//  GamePlayLayer.cpp
//  SquareClear
//
//  Created by 徐徐 on 15/11/14.
//
//

#include "GamePlayLayer.h"
#include "SquareGroup.h"
USING_NS_CC;

bool GamePlayLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    m_gameBoardHeight = m_squareRowCount * m_squareHeight;
    m_gameBoardWidth = m_squareColumnCount * m_squareWidth;
    m_BackgroundBoard = new int[m_squareRowCount * m_squareColumnCount];
    //test
    for(int i = 0;i < m_squareRowCount * m_squareColumnCount; i++)
    {
        m_BackgroundBoard[i] = 0;
        if(i > 14 && i < 100)
        {
            m_BackgroundBoard[i] = 1;
        }
    }
    
    auto s = Director::getInstance()->getWinSize();
    
    m_drawNode = DrawNode::create();
    addChild(m_drawNode, 10);

    //m_drawNode->drawSolidRect(Vec2(10,10), Vec2(200,200), Color4F(1,1,0,1));
    
    //test
    //drawSquare();
	auto sgtest = SquareGroup::create();
	sgtest->setAnchorPoint(Vec2(0, 0));
	sgtest->SetSquareGroup(10, 20, SquareGroup::ST_L, Square::SC_BLUE);
	sgtest->setPosition(Vec2(100,200));
    //drawSquareGroup(sgtest, 100, 200);
	sgtest->DrawGroup(m_squareWidth, m_squareHeight);
	addChild(sgtest, 100);
    return true;
}

GamePlayLayer::~GamePlayLayer()
{
    delete[] m_BackgroundBoard;
}
void GamePlayLayer::drawSquare()
{
    for(int i = 0;i < m_squareRowCount * m_squareColumnCount; i++)
    {
        float _x = (i % m_squareColumnCount) * m_squareWidth;
        float _y = (i / m_squareColumnCount) * m_squareHeight;
        if(m_BackgroundBoard[i] == 0)
        {
            m_drawNode->drawSolidRect(Vec2(_x,_y), Vec2(_x + m_squareWidth, _y + m_squareHeight), Color4F(1,0,0,1));
        }
        else
        {
            m_drawNode->drawSolidRect(Vec2(_x,_y), Vec2(_x + m_squareWidth, _y + m_squareHeight),  Color4F(0,1,0,1));
        }
    }
}


void GamePlayLayer::drawSquareGroup(SquareGroup* sg,int x,int y)
{
    SquareMap* sm = sg->getGroupArray();
    SquareMapIterator smit;
    for(smit = sm->begin(); smit!=sm->end(); smit++)
    {
        drawOneSquare(x, y, smit->second);
    }
    
}

void GamePlayLayer::drawOneSquare(int x,int y,Square* sq)
{
	Vec2 _x = Director::getInstance()->convertToGL(Vec2(x + m_squareWidth * sq->GetX(), y + m_squareHeight * sq->GetY()));
	Vec2 _y = Director::getInstance()->convertToGL(Vec2(x + m_squareWidth * (sq->GetX() + 1), y + m_squareHeight * (sq->GetY() + 1)));
    m_drawNode->drawSolidRect(_x, _y, sq->getColor4F());
}
