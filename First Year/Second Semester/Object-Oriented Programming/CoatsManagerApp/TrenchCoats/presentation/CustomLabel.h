#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>
#include <QString>

class CustomLabel : public QLabel {
public:
    CustomLabel(const QString& text);
};

#endif // CUSTOMLABEL_H
