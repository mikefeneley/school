#include "TennisController.h"
#include <iostream>

TennisController::TennisController(QWidget *parent, TennisModel *model) : QWidget(parent)
{
	tennis_model = model;
	new_game = true;
	player1_hit = false;
	player2_hit = true;

}

/**
 * Interprets the keyPress and adjusts the game model accordingly.
 *
 * Pre:  TennisController has been initializesd.
 * 
 * Post: Game model has been updated if a supported key has been pressed.
 *       
 */
void TennisController::KeyEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Q) {
		exit(EXIT_SUCCESS);
	} else if(event->key() == Qt::Key_A) {
		Player1Down();
	} else if(event->key() == Qt::Key_S) {
		Player1Up();
	} else if(event->key() == Qt::Key_K) {
		Player2Down();
	} else if(event->key() == Qt::Key_L) {
		Player2Up();
	}
}
/**
 * Moves player 1 paddle to higher position on board.
 */
void TennisController::Player1Up()
{
	if(tennis_model->player1.top() - MOVE_DISTANCE >= 0)
	{
		tennis_model->player1.translate(0, -MOVE_DISTANCE);
		emit GameChange();
	}
}

/**
 * Moves player 2 paddle to higher position on board.
 */
void TennisController::Player2Up()
{
	if(tennis_model->player2.top() - MOVE_DISTANCE >= 0)
	{
		tennis_model->player2.translate(0, -MOVE_DISTANCE);
		emit GameChange();
	}
}
/**
 * Moves player 1 paddle to lower position on board.
 */
void TennisController::Player1Down()
{
	if(tennis_model->player1.bottom() + MOVE_DISTANCE <= WINDOW_HEIGHT) 
	{
		tennis_model->player1.translate(0, MOVE_DISTANCE);
		emit GameChange();
	}
}
/**
 * Moves player 2 paddle to lower position on board.
 */
void TennisController::Player2Down()
{
	if(tennis_model->player2.bottom() + MOVE_DISTANCE <= WINDOW_HEIGHT) 
	{
		tennis_model->player2.translate(0, MOVE_DISTANCE);
		emit GameChange();
	}
}

	
/**
 * Provides continuous update to the game board by moving the ball, updating
 * the player scores, and starting new games. 
 * Provides 3 second delay in between new games.
 *
 * Pre:  TennisController has been initializesd.
 *       
 */
void TennisController::EngineUpdate()
{
	if(new_game) {
		sleep(WAIT_TIME);
		new_game = false;
	}


	double new_x = tennis_model->BallX() + tennis_model->X_Direction() * 2;
	double new_y = tennis_model->BallY() + tennis_model->Y_Direction() * 2;
	tennis_model->ball.setX(new_x);
	tennis_model->ball.setY(new_y);


	// Check for collision with player paddles.
	if(new_y >= tennis_model->player1.top() && new_y <= tennis_model->player1.bottom()) {
		if(new_x - BALL_RADIUS <= tennis_model->player1.right() && !player1_hit) {
			tennis_model->InvertX();
			player1_hit = true;
			player2_hit = false;
		}
	}
	if(new_y >= tennis_model->player2.top() && new_y <= tennis_model->player2.bottom()) {
		if(new_x + BALL_RADIUS >= tennis_model->player2.left() && !player2_hit) {
			tennis_model->InvertX();
			player2_hit = true;
			player1_hit = false;
		}
	}


	// Check for ball collision with walls.
	if(new_x - BALL_RADIUS <= 0) {
		Player2Win();
	}
	if(new_y - BALL_RADIUS <= 0) {
		tennis_model->InvertY();
	}
	if(new_y + BALL_RADIUS >= WINDOW_HEIGHT) {
		tennis_model->InvertY();
	}
	if(new_x + BALL_RADIUS >= WINDOW_WIDTH) {
		Player1Win();
	}

	emit GameChange();
}

/*
 * Updates player1 score and starts new game.
 */
void TennisController::Player1Win()
{
	new_game = true;
	tennis_model->player1_score++;
	if(tennis_model->player1_score == 10) {
		tennis_model->player1_score = 0;
	}
	tennis_model->ResetBall();
	emit GameChange();

}
/*
 * Updates player2 score and starts new game.
 */
void TennisController::Player2Win()
{
	new_game = true;
	tennis_model->player2_score++;
	if(tennis_model->player2_score == 10) {
		tennis_model->player2_score = 0;
	}
	tennis_model->ResetBall();
	emit GameChange();

}