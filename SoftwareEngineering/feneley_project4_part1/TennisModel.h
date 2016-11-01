#ifndef TENNIS_MODEL
#define TENNIS_MODEL
 

#include <QRect>
#include <QPoint>
#include <math.h>
#include "Constants.h"

/**
 * TennisModel.h
 *
 * Acts as a model for a game of virtual tennis in
 * the MVC pattern.
 *  
 */
class TennisModel 
{

	public:
		TennisModel();
		void ResetBall();
		void InvertX();
		void InvertY();
		int Player1_Score();
		int Player2_Score();
		double BallX();
		double BallY();
		double X_Direction();
		double Y_Direction();

	public:
		QRect player1;
		QRect player2;
		QPointF ball;
		int player1_score;
		int player2_score;
		double x_direction;
		double y_direction;
};



#endif