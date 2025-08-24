#include <QVBoxLayout>
#include <QPushButton>
#include <QPalette>

#include "navigation_drawer.h"

NavigationDrawer::NavigationDrawer(QWidget *parent) : QWidget{parent} {
    //setMinimumWidth(MIN_WIDTH);
    setGeometry(-parent->width() * 0.4, 0, parent->width() * 0.4, parent->height());
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(240, 240, 240));
    setPalette(pal);
    setAutoFillBackground(true);
    auto *root_v_layout = new QVBoxLayout(this);
    auto *btn1 = new QPushButton("example btn");
    root_v_layout->addWidget(btn1);
}

void NavigationDrawer::setExpansionProgress(qreal progress) {
    m_expansionProgress = progress;
    adjustPosition();
}

//???
void NavigationDrawer::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    adjustPosition();
}

void NavigationDrawer::adjustPosition() {
    setGeometry((m_expansionProgress - 1) * parentWidget()->width() * 0.4, 0,
                parentWidget()->width() * 0.4, parentWidget()->height());
}
