#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include "SyntaxHighlighter.h"
#include <QWheelEvent>
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
#include <QModelIndex>

class SyntaxHighlighter;
class KeyFilter;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_comboBoxType_currentIndexChanged(int index);
    void on_Send_clicked();
    void on_tableViewHistory_doubleClicked(const QModelIndex &index);
    void on_textEdit_textChanged();

    void on_pushButton_toggled(bool checked);

private:
    Ui::Widget *ui;
    QStandardItemModel *model;
    SyntaxHighlighter *m_HighLight;
    KeyFilter* pFilter;
    //QTableView* tableViewHistory;

    int Row = 0;
    int State = 0;

};

class KeyFilter : public QObject {
    int State = 0;
protected:
    bool eventFilter(QObject* pobj, QEvent* pe);
public:
    KeyFilter(QObject* pobj = nullptr): QObject(pobj){}
    void SetState(int state);
};
#endif // WIDGET_H
