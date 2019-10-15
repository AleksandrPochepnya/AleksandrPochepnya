#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>

#define plain 0
#define flash 1
#define binarry 2

#define firstcoll 0
#define secondcoll 1
#define thirdcoll 2
#define fourthcoll 3

#define maxrow 5

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //tableViewHistory = new QTableView();
    model = new QStandardItemModel(5,4, ui->tableViewHistory);
    ui->tableViewHistory->setModel(model);

    model->setHeaderData(firstcoll, Qt::Horizontal, tr("From"));
    model->setHeaderData(secondcoll, Qt::Horizontal, tr("Text"));
    model->setHeaderData(thirdcoll, Qt::Horizontal, tr("Type"));
    model->setHeaderData(thirdcoll, Qt::Horizontal, tr("Date"));

    for(int row=0; row!=model->rowCount(); ++row){
        model->setHeaderData(row, Qt::Vertical, tr(""));
    }

    ui->tableViewHistory->setColumnHidden(2, true);
    ui->tableViewHistory->setColumnHidden(3, true);

    ui->tableViewHistory->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewHistory->horizontalHeader()->setStretchLastSection(true);
    connect(ui->tableViewHistory,&QAbstractItemView::doubleClicked,this, &Widget::on_tableViewHistory_doubleClicked);
    ui->tableViewHistory->hide();

    m_HighLight = new SyntaxHighlighter(ui->textEdit->document());

    pFilter = new KeyFilter(ui->textEdit);
    ui->textEdit->installEventFilter(pFilter);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_comboBoxType_currentIndexChanged(int index)
{
    if(index == binarry){
        ui->Isdn->hide();
        ui->lineEditIsdn->hide();
        ui->textEdit->clear();
    }
    else{
        if (State == binarry)
            ui->textEdit->clear();
        ui->Isdn->show();
        ui->lineEditIsdn->show();
    }
    State = index;
    m_HighLight->SetState(State);
    pFilter->SetState(State);
}

void Widget::on_Send_clicked()
{
    if(Row == maxrow)
        Row = 4;
    QStandardItem* ptwifirst = nullptr;
    QStandardItem* ptwisecond = nullptr;
    QStandardItem* ptwithird = nullptr;
    QStandardItem* ptwifourth = nullptr;
    if(State == binarry){
        ptwifirst = new QStandardItem("");
    }else{
        ptwifirst = new QStandardItem(ui->lineEditIsdn->text());
    }
    ptwisecond = new QStandardItem(ui->textEdit->toPlainText());
    ptwithird = new QStandardItem(QString::number(State));
    ptwifourth = new QStandardItem(QDateTime::currentDateTime().toString());

    model->setItem(Row, firstcoll, ptwifirst);
    model->setItem(Row, secondcoll, ptwisecond);
    model->setItem(Row, thirdcoll, ptwithird);
    model->setItem(Row, fourthcoll, ptwifourth);
    model->sort(fourthcoll, Qt::DescendingOrder);

    ++Row;
}

void Widget::on_tableViewHistory_doubleClicked(const QModelIndex &index)
{
    if(index.column() == firstcoll){
        if(model->item(index.row(), index.column())){
            ui->lineEditIsdn->setText(model->item(index.row(), index.column())->text());            
            State = model->item(index.row(), thirdcoll)->text().toInt();
            ui->comboBoxType->setCurrentIndex(State);
            m_HighLight->SetState(State);
            pFilter->SetState(State);
            ui->textEdit->setPlainText(model->item(index.row(), secondcoll)->text());
        }
    }else{
        if(model->item(index.row(), index.column())){
            ui->lineEditIsdn->setText(model->item(index.row(), firstcoll)->text());
            State = model->item(index.row(), thirdcoll)->text().toInt();
            ui->comboBoxType->setCurrentIndex(State);
            m_HighLight->SetState(State);
            pFilter->SetState(State);
            ui->textEdit->setPlainText(model->item(index.row(), index.column())->text());
        }
    }
}

void Widget::on_textEdit_textChanged()
{
    if(State == binarry){
        QTextCursor  cursor = ui->textEdit->textCursor();
        auto pos = cursor.position();
        QString text = ui->textEdit->toPlainText();
        auto lenth = text.length();
        //text.replace(QRegExp("[^A-F]"), "");
        text.replace(" ", "");
        QStringList tokens;
        for(int i = 0; i < text.length(); i += 2) {
            tokens << text.mid(i, 2);
        }
        ui->textEdit->blockSignals(true);
        ui->textEdit->setText(tokens.join(" "));
        ui->textEdit->moveCursor(QTextCursor::EndOfBlock);
        ui->textEdit->blockSignals(false);
        auto lenthlast = ui->textEdit->toPlainText().length();
        if(lenthlast > lenth) ++pos;
        cursor.setPosition(pos);
        ui->textEdit->setTextCursor(cursor);
    }
}

bool KeyFilter::eventFilter(QObject* pobj, QEvent* pe)
{
    if (pe->type() == QEvent::KeyPress) {
        if (static_cast<QKeyEvent*>(pe)->key() == Qt::Key_Backspace && State == binarry) {
            QTextEdit* text = qobject_cast<QTextEdit*>( pobj);
            if(text){
                auto cursor = text->textCursor();
                auto pos = cursor.position();
                if(pos && text->toPlainText().at(--pos) == " "){
                    cursor.setPosition(pos);
                    text->setTextCursor(cursor);
                }
            }
        }
    }
    return false;
}

void KeyFilter::SetState(int state)
{
    State = state;
}



void Widget::on_pushButton_toggled(bool checked)
{
    if(checked)
        ui->tableViewHistory->show();
    else
        ui->tableViewHistory->hide();
}
