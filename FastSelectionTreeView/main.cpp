#include "mytreeview.hpp"

#include <QApplication>
#include <QStandardItemModel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStandardItemModel model;
    model.setHorizontalHeaderLabels({"Items"});

    QStandardItem *parent1 = new QStandardItem("Parent A");
    QStandardItem *parent2 = new QStandardItem("Parent B");
    QStandardItem *parent3 = new QStandardItem("Parent C");
    QStandardItem *parent4 = new QStandardItem("Parent D");

    for (int i = 0; i < 5; ++i) {
        parent1->appendRow(new QStandardItem("Child A" + QString::number(i)));
        parent3->appendRow(new QStandardItem("Child C" + QString::number(i)));
        parent4->appendRow(new QStandardItem("Child D" + QString::number(i)));
    }

    const int parentSize2 = 15, childSize2 = 3;
    for (int i = 0; i < parentSize2; ++i)
    {
        QStandardItem *child = new QStandardItem("Child " + QString::number(i));
        for (int j = 0; j < childSize2; ++j) {
            child->appendRow(new QStandardItem("SubChild " + QString::number(j)));
        }
        parent2->appendRow(child);
    }

    model.appendRow(parent1);
    model.appendRow(parent2);
    model.appendRow(parent3);
    model.appendRow(parent4);

    MyTreeView tree;
    tree.setModel(&model);
    tree.setWindowTitle("QTreeView Subtree Fast Selection");
    tree.resize(300, 600);
    tree.show();

    return app.exec();
}

#include "main.moc"
