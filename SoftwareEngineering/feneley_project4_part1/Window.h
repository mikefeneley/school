#ifndef WINDOW_H
#define WINDOW_H

#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <time.h>

#include "Constants.h"
#include "TennisView.h"
#include "TennisModel.h"
#include "TennisController.h"



/*
 * Window.h
 *
 * Main window pannel that holds the MVC objects for the game
 * VirtualTennis 
 *
 */
class Window : public QWidget
{
	Q_OBJECT


	public:
	    Window();

	protected:
		void keyPressEvent(QKeyEvent *event);

	private:
		TennisView *view;
		TennisModel *model;
		TennisController *controller;
 		QTimer *timer;
};






#endif