#ifndef TENNIS_CONTROLLER_H
#define TENNIS_CONTROLLER_H
 
#include <QObject>
#include <QWidget>
#include <QRect>
#include <QPoint>
#include <QKeyEvent>
#include <QTimer>
#include <unistd.h>
#include "Constants.h"
#include "TennisModel.h"

/**
 * TennisController.h
 *
 * Performs the function of controller in the MVC pattern.
 * Recieves input from the Window class and interprets the 
 * input to make changes to the game model.  
 *  
 */
class TennisController : public QWidget
{	
	Q_OBJECT


	public:
		TennisController(QWidget *parent, TennisModel *model);
		void KeyEvent(QKeyEvent *event);

	signals:
		void GameChange();

	public slots:
		void EngineUpdate();

	private:
		void Player1Up();
		void Player2Up();
		void Player1Down();
		void Player2Down();
		void Player1Win();
		void Player2Win();

	private:
		TennisModel *tennis_model;
		bool new_game;
		bool player1_hit;
		bool player2_hit;
};


#endif