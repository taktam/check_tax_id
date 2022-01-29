#ifndef CHECKWINDOW_H
#define CHECKWINDOW_H

#include <QMainWindow>
#include <QtGlobal>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class CheckWindow; }
QT_END_NAMESPACE


class CheckWindow : public QMainWindow
{
    Q_OBJECT

public:
    CheckWindow(QWidget *parent = nullptr);
    ~CheckWindow();


private slots:
    void on_name_edit_textChanged(const QString &arg1);
    void on_tax_edit_textChanged(const QString &arg1);
    void on_checkButton_clicked();

private:
    Ui::CheckWindow *ui;
    QString name = "none";
    QString tax_string = "none";
    QMap<QString, QString> irscode;
    QMap<QString, QString> taxcode;
    int checksum;
    QString IRS;
    QString Tcode;

};
#endif // CHECKWINDOW_H
