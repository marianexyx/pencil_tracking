#ifndef POSEBODYPARTPOINT_H
#define POSEBODYPARTPOINT_H

struct poseBodyPartPoint
{
    double x;
    double y;
    double c;

    void showPointInDebug()
    {
        qDebug() << "x =" << x << ", y =" << y << ", c =" << c;
    }
};

#endif // POSEBODYPARTPOINT_H
