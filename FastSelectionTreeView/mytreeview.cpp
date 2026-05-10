#include "mytreeview.hpp"
#include <QMouseEvent>
#include <QSignalBlocker>
#include <queue>

MyTreeView::MyTreeView(QWidget* parent)
    : QTreeView(parent)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MyTreeView::mousePressEvent(QMouseEvent* event)
{
    if ( event->button()   == Qt::LeftButton &&
        (event->modifiers() & Qt::ControlModifier) == 0 &&
        (event->modifiers() & Qt::ShiftModifier) == 0 )
    {
        m_clickedIndex = indexAt(event->pos());
    } else {
        m_clickedIndex = QModelIndex();
    }

    QTreeView::mousePressEvent(event);
}

void MyTreeView::selectionChanged(const QItemSelection& selected,
                                  const QItemSelection& deselected)
{
    QSignalBlocker blocker(selectionModel());

    QItemSelection sel, desel;
    for (const QModelIndex& id : selected.indexes()) {
        collectChildren(id, sel, false);
    }

    for (const QModelIndex& id : deselected.indexes()) {
        collectChildren(id, desel, false);
    }

    if (m_clickedIndex.isValid())
    {
        QItemSelection clickSel;
        collectChildren(m_clickedIndex, clickSel, true);
        sel.merge(clickSel, QItemSelectionModel::Select);
    }

    selectionModel()->select(desel, QItemSelectionModel::Deselect);
    selectionModel()->select(sel, QItemSelectionModel::Select);

    viewport()->update();
}

void MyTreeView::collectChildren(const QModelIndex& root, QItemSelection& out, bool includeRoot)
{
    if (!root.isValid()) {
        return;
    }

    if (includeRoot) {
        out.select(root, root);
    }

    std::queue<QModelIndex> queue;
    queue.push(root);

    while (!queue.empty())
    {
        QModelIndex id = queue.front();
        queue.pop();

        if (const int rowCount = model()->rowCount(id); rowCount > 0)
        {
            QModelIndex firstChild = model()->index(0, 0, id);
            QModelIndex lastChild  = model()->index(rowCount - 1, 0, id);
            out.select(firstChild, lastChild);

            for (int row{}; row < rowCount; ++row) {
                if (QModelIndex child = model()->index(row, 0, id); child.isValid()) {
                    queue.push(child);
                }
            }
        }
    }
}
