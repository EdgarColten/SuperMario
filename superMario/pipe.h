#ifndef PIPE_H
#define PIPE_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>

class Pipe : public QLabel
{
    Q_OBJECT
public:
    Pipe(const QString &imagePath, QWidget *parent = nullptr);
};

#endif // PIPE_H
