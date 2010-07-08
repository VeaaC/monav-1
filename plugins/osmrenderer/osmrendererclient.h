/*
Copyright 2010  Christian Vetter veaac.fdirct@gmail.com

This file is part of MoNav.

MoNav is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MoNav is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MoNav.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAPNIKRENDERER_H
#define MAPNIKRENDERER_H

#include <QObject>
#include <QCache>
#include <QNetworkAccessManager>
#include "interfaces/irenderer.h"

class OSMRendererClient : public QObject, IRenderer
{
	Q_OBJECT
	Q_INTERFACES( IRenderer )

public:

	 OSMRendererClient();
	~OSMRendererClient();
	virtual QString GetName();
	virtual void SetInputDirectory( const QString& dir );
	virtual void ShowSettings();
	virtual bool LoadData();
	virtual int GetMaxZoom();
	virtual ProjectedCoordinate Move( ProjectedCoordinate center, int shiftX, int shiftY, int zoom );
	virtual ProjectedCoordinate PointToCoordinate( ProjectedCoordinate center, int shiftX, int shiftY, int zoom );
	virtual ProjectedCoordinate ZoomInOn( ProjectedCoordinate center, ProjectedCoordinate zoomPoint, int zoom );
	virtual ProjectedCoordinate ZoomOutOn( ProjectedCoordinate center, ProjectedCoordinate zoomPoint, int zoom );
	virtual bool Paint( QPainter* painter, const PaintRequest& request );
	virtual void setSlot( QObject* obj, const char* slot );

signals:
	void changed();

public slots:
	void finished( QNetworkReply* reply );

protected:

	void unload();
	void setupPolygons();
	void drawArrow( QPainter* painter, int x, int y, double rotation, QColor outer, QColor inner );
	void drawIndicator( QPainter* painter, const QTransform& transform, const QTransform& inverseTransform, int x, int y, int sizeX, int sizeY, QColor outer, QColor inner );

	QCache< long long, QPixmap > cache;
	QNetworkAccessManager* network;
	int tileSize;
	bool loaded;
	QPolygonF arrow;
	long long cacheSize;
};

#endif // MAPNIKRENDERER_H