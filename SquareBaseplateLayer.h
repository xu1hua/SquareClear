//
//
//
//	Created by xuhua on 16/5/10
//  游戏的基板类，将方块置于基板的空格中
//
//

#ifndef SquareBaseplateLayer_h
#define SquareBaseplateLayer_h

#include <stdio.h>
#include "cocos2d.h"

class Square;
struct BaseSize
{
	int width;
	int height;
	BaseSize(int x, int y)
	{
		width = x;
		height = y;
	}
};
enum SquareBaseplateState
{
	SQBS_EMPTY = 0,
	SQBS_MAP,
	SQBS_FRAME,
	SQBS_SQUARE,
	SQBS_MAX
};
struct BaseSquare
{
	SquareBaseplateState squareState;
	Square* pSquare;
	BaseSquare(SquareBaseplateState ss,Square* sq)
	{
		squareState = ss;
		pSquare = sq;
	}
};
class SquareBaseplateLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(SquareBaseplateLayer);

    SquareBaseplateLayer();
	~SquareBaseplateLayer();

	static SquareBaseplateLayer * getInstance()
	{
		return s_pSquareBaseplateLayer;
	}
	virtual bool init() override;

    void drawBasesplate(cocos2d::Vec2 squareSize);

	void drawBasesplate();
	//将所有Frame的放块设回Empty
	void clearFrameSquare();
	//检查坐标点对应的基板是否为空方块
	//return 如果为空。则返回对应的index
	//		如果不空，返回-1
	int checkSquareIsEmptyOrFrame(cocos2d::Vec2 point);
	//将index号的方块设为有边框
	void setFrame(int index);
	//获得index号方块的世界坐标
	cocos2d::Vec2 getWorldPos(int index);
	//将index号方块设为占用
	void PlaceSquare(int index);
	CC_SYNTHESIZE(BaseSize, _baseSize, BaseSize);
	CC_SYNTHESIZE(cocos2d::Vec2, _squareSize, SquareSize);
private:
	std::vector<BaseSquare> *m_baseSquareList;
    cocos2d::DrawNode * m_drawNode;
	
	static SquareBaseplateLayer* s_pSquareBaseplateLayer;
};

#endif//define SquareBaseplateLayer_h