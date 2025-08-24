#ifndef NAVIGATION_DRAWER_H
#define NAVIGATION_DRAWER_H

#include <QWidget>

class NavigationDrawer : public QWidget {
    Q_OBJECT
    Q_PROPERTY(qreal expansionProgress READ expansionProgress WRITE setExpansionProgress)
public:
    explicit NavigationDrawer(QWidget *parent = nullptr);
    qreal expansionProgress() const { return m_expansionProgress; }
    void setExpansionProgress(qreal progress);
    bool isExpanded() const { return m_isExpanded; }
    void setExpanded(bool expanded) { m_isExpanded = expanded; }

signals:

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    qreal m_expansionProgress{0.0};
    bool m_isExpanded{false};

    void adjustPosition();

    static constexpr int MIN_WIDTH = 200;
};

#endif  // NAVIGATION_DRAWER_H
