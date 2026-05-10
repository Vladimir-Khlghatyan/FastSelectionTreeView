#ifndef MYTREEVIEW_HPP
#define MYTREEVIEW_HPP

#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelection>

class MyTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit MyTreeView(QWidget *parent = nullptr);
    virtual ~MyTreeView() {}

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void selectionChanged(const QItemSelection& selected,
                          const QItemSelection& deselected) override;

private:
    void collectChildren(const QModelIndex& root, QItemSelection& out, bool includeRoot);

    QModelIndex m_clickedIndex;

};

#endif // MYTREEVIEW_HPP
