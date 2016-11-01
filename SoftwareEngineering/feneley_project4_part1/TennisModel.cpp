#include "TennisModel.h"

/*
 * Intialize game model object.
 */
TennisModel::TennisModel()
{	
	player1_score = 0;
	player2_score = 0;
	player1.setRect(WALL_DISTANCE, (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2, PADDLE_WIDTH, PADDLE_HEIGHT);
	player2.setRect(WINDOW_WIDTH - WALL_DISTANCE - PADDLE_WIDTH, (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2, PADDLE_WIDTH, PADDLE_HEIGHT);
	ResetBall();
}
/*
 * Moves the ball to the middle of the game board and generates a random
 * direction in which to move.
 */
void TennisModel::ResetBall()
{
	ball.setX(WINDOW_WIDTH / 2);
	ball.setY((rand() % (WINDOW_HEIGHT - BALL_RADIUS * 2)) + BALL_RADIUS);

	double degrees = (rand() % 45) + 15;
	double radians = degrees * CONVERSION;
	y_direction = sin(radians);
	x_direction = cos(radians);


	// Change direction in approximately half of the cases.
	int num = rand();
	if(num % 2 == 0) {
		InvertX();
	}
	num = rand();
	if(num % 2 == 0) {
		InvertY();
	}
}


/* 
 * Switches ball x direction when paddle is hit.
 */
void TennisModel::InvertX()
{
	x_direction = -x_direction;
}
/* 
 * Switches ball y direction when paddle is hit.
 */
void TennisModel::InvertY()
{
	y_direction = -y_direction;
}


int TennisModel::Player1_Score()
{
	return player1_score;
}
int TennisModel::Player2_Score()
{
	return player2_score;
}
double TennisModel::X_Direction()
{
	return x_direction;
}
double TennisModel::Y_Direction()
{
	return y_direction;
}
double TennisModel::BallX()
{
	return ball.x();
}
double TennisModel::BallY()
{
	return ball.y();
}