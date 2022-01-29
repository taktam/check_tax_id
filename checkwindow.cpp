#include "checkwindow.h"
#include "ui_checkwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>

CheckWindow::CheckWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CheckWindow)
{
    ui->setupUi(this);
    this->setFixedSize(510,155);
    irscode["Baranya_1"] = "02";
    irscode["Baranya_2"] = "22";
    irscode["Bács-Kiskun_1"] = "03";
    irscode["Bács-Kiskun_2"] = "23";
    irscode["Békés_1"] = "04";
    irscode["Békés_2"] = "24";
    irscode["Borsod-Abaúj-Zemplén_1"] = "05";
    irscode["Borsod-Abaúj-Zemplén_2"] = "25";
    irscode["Csongrád-Csanád_1"] = "06";
    irscode["Csongrád-Csanád_2"] = "26";
    irscode["Fejér_1"] = "07";
    irscode["Fejér_2"] = "27";
    irscode["Győr-Moson-Sopron_1"] = "08";
    irscode["Győr-Moson-Sopron_2"] = "28";
    irscode["Hajdú-Bihar_1"] = "09";
    irscode["Hajdú-Bihar_2"] = "29";
    irscode["Heves_1"] = "10";
    irscode["Heves_2"] = "30";
    irscode["Komárom-Esztergom_1"] = "11";
    irscode["Komárom-Esztergom_2"] = "31";
    irscode["Nógrád_1"] = "12";
    irscode["Nógrád_2"] = "32";
    irscode["Pest_1"] = "13";
    irscode["Pest_2"] = "33";
    irscode["Somogy_1"] = "14";
    irscode["Somogy_2"] = "34";
    irscode["Szabolcs-Szatmár-Bereg_1"] = "15";
    irscode["Szabolcs-Szatmár-Bereg_2"] = "35";
    irscode["Jász-Nagykun-Szolnok_1"] = "16";
    irscode["Jász-Nagykun-Szolnok_2"] = "36";
    irscode["Tolna_1"] = "17";
    irscode["Tolna_2"] = "37";
    irscode["Vas_1"] = "18";
    irscode["Vas_2"] = "38";
    irscode["Veszprém_1"] = "19";
    irscode["Veszprém_2"] = "39";
    irscode["Zala_1"] = "20";
    irscode["Zala_2"] = "40";
    irscode["Észak-Budapest"] = "41";
    irscode["Kelet-Budapest"] = "42";
    irscode["Dél-Budapest"] = "43";
    irscode["Kiemelt Adózók Adóigazgatósága"] = "44";
    irscode["Kiemelt Ügyek Adóigazgatósága"] = "51";

    taxcode["1"] = "Untaxed by basic right";
    taxcode["2"] = "Untaxed function";
    taxcode["3"] = "According to standard rules";
    taxcode["4"] = "EVA";
    taxcode["5"] = "Tax payer groups";
 }

CheckWindow::~CheckWindow()
{
    delete ui;
}



void CheckWindow::on_name_edit_textChanged(const QString &arg1)
{
    name = arg1;
}


void CheckWindow::on_tax_edit_textChanged(const QString &arg1)
{
    tax_string = arg1;
}


void CheckWindow::on_checkButton_clicked()
{
    if ((name == "none")|(name == ""))
        QMessageBox::information(this, "Company name fault", "The name of the company is missing.");
    else
        if ((tax_string == "none")|(tax_string == ""))
            QMessageBox::information(this, "Tax ID fault", "The Tax number is missing.");
        else
            if (name.count(QRegExp("[§#*~]")) > 0)
                QMessageBox::information(this, "Company name fault", "The name  does not contain these characters:\n § # * ~ ");
            else
                if (tax_string.length() < 11)
                    QMessageBox::information(this, "Tax ID fault", "The tax ID is eleven digits");
                else
                {
                    int sum = (tax_string[0].digitValue()*9)+(tax_string[1].digitValue()*7)+(tax_string[2].digitValue()*3)+(tax_string[3].digitValue())+(tax_string[4].digitValue()*9)+(tax_string[5].digitValue()*7)+(tax_string[6].digitValue()*3);
                    if (sum%10 == 0)
                        checksum = 0;
                    else
                        checksum = 10 - (sum%10);
                    if (tax_string[7].digitValue() != checksum)
                        QMessageBox::information(this, "Tax ID fault", "Checksum Error");
                    else
                    {
                        if ((tax_string[8].digitValue()==0)|(tax_string[8].digitValue()>5))
                            QMessageBox::information(this, "Tax ID fault", "Tax key error\nPossible keys: 1-5");
                        else
                        {
                            QString authCode;
                            authCode = authCode + tax_string[9] +tax_string[10];
                            QMap<QString,QString>::const_iterator i = irscode.constBegin();
                            IRS = "none";
                            while (i != irscode.constEnd())
                            {
                                if (i.value() == authCode)
                                    IRS = i.key();
                                ++i;
                            }
                            if (IRS == "none")
                                QMessageBox::information(this, "IRS Code fault", "IRS key error\nNot valid key");
                            else
                            {
                                QMap<QString,QString>::const_iterator i = taxcode.constBegin();
                                while (i != taxcode.constEnd())
                                {
                                    if (i.key() == tax_string[8])
                                        Tcode = i.value();
                                    ++i;
                                }
                                ui->outputData->setText("Name:\t " + name+"\nTax Nr.:\t" + tax_string+"\nTax code:\t" + Tcode+"\nOffice:\t" + IRS);
                            }
                        }
                    }
                }

}

