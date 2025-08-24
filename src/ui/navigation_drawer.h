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

    static constexpr int ANIME_MS = 250;
signals:

protected:
    void resizeEvent(QResizeEvent *event) override;
    void leaveEvent(QEvent *event) override { emit requestCollapse(); }
    void enterEvent(QEnterEvent *event) override { emit requestExpand(); }

private:
    qreal m_expansionProgress{0.0};
    bool m_isExpanded{false};

    void adjustPosition();

    static constexpr int MIN_WIDTH = 200;

signals:
    void requestCollapse();
    void requestExpand();
};

#endif  // NAVIGATION_DRAWER_H
