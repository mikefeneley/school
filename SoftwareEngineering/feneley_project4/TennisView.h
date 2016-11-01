#ifndef TENNNISVIEW_H
#define TENNNISVIEW_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QString>
#include "Constants.h"
#include "TennisModel.h"


/**
 * TennisView.h
 *
 * Acts as a view for a game of virtual tennis in
 * the MVC pattern. Displays all the information contained
 * in the tennis_model.
 *  
 */
class TennisView : public QWidget
{
	Q_OBJECT


	public:
	    TennisView(QWidget *parent, TennisModel *model);

	public slots:
		void RefreshDisplay();

	protected:
	    void paintEvent(QPaintEvent* event);

	private:
		QString GetPlayer1Score();
		QString GetPlayer2Score();

	private:
		TennisModel *tennis_model;

};

#endif