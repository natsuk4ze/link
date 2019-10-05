//=====================================
//
//FieldConfig.h
//機能:フィールド関連の設定値
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCONFIG_H_
#define _FIELDCONFIG_H_


namespace Field
{		
	/**************************************
	PlaceModelの座標構造体
	***************************************/
	struct FieldPosition
	{
		int x, z;

		FieldPosition()
		{
			x = 0;
			z = 0;
		}

		FieldPosition(int x, int z)
		{
			this->x = x;
			this->z = z;
		}
	};

	/**************************************
	フィールドの移動可能な境界
	***************************************/
	struct FieldBorder
	{
		int forward;		//Zプラス方向の境界
		int right;			//Xプラス方向の境界
		int back;			//Zマイナス方向の境界
		int left;			//Zマイナス方向の境界

		FieldBorder(int forward, int right, int back, int left) :
			forward(forward), right(right), back(back), left(left)
		{

		}
	};
}

#endif