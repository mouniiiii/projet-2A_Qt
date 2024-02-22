#include "messagerie.h"
#include "ui_messagerie.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>
messagerie::messagerie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messagerie),
    messageModel(new QStandardItemModel(this))

{
    ui->setupUi(this);
loadMessages();
}


messagerie::~messagerie()
{
    delete ui;

       delete messageModel;
}



void messagerie::on_pushButton_Mainenvoyer_clicked()
{
    // Get the message text from the UI
        QString messageText = ui->lineEdit->toPlainText().trimmed();
        if (messageText.isEmpty()) {
            return;
        }

        // Insert the message into the database
        QSqlQuery query(database);
        query.prepare("INSERT INTO chat_messages (sender_id, receiver_id, message_text, is_read, timestamp, is_deleted) "
                      "VALUES (?, ?, ?, ?, ?, ?)");
        query.bindValue(0, 1); // Change this to the ID of the current user
        query.bindValue(1, 2); // Change this to the ID of the recipient user
        query.bindValue(2, messageText);
        query.bindValue(3, false);
        query.bindValue(4, QDateTime::currentDateTime());
        query.bindValue(5, false);
        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to send message");
            return;
        }

        // Add the message to the message model
        QString message = QString("[%1] You: %2").arg(QDateTime::currentDateTime().toString(Qt::ISODate)).arg(messageText);
        messageModel->appendRow(new QStandardItem(message));

        // Clear the message text edit
        ui->messageTextEdit->clear();
}
