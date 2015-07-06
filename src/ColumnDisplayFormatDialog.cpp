#include "ColumnDisplayFormatDialog.h"
#include "ui_ColumnDisplayFormatDialog.h"

ColumnDisplayFormatDialog::ColumnDisplayFormatDialog(const QString& colname, QString current_format, QWidget* parent)
    : QDialog(parent),
      ui(new Ui::ColumnDisplayFormatDialog),
      column_name(colname)
{
    // Create UI
    ui->setupUi(this);
    ui->comboDisplayFormat->addItem(tr("Default"), "default");
    ui->comboDisplayFormat->addItem(tr("Lower case"), "lower");
    ui->comboDisplayFormat->addItem(tr("Upper case"), "upper");
    ui->comboDisplayFormat->addItem(tr("Unix epoch to date"), "epoch");
    ui->comboDisplayFormat->addItem(tr("Julian day to date"), "julian");
    ui->comboDisplayFormat->addItem(tr("Round number"), "round");
    ui->labelDisplayFormat->setText(ui->labelDisplayFormat->text().arg(column_name));

    // Set the current format, if it's empty set the default format
    if(current_format.isEmpty())
    {
        ui->comboDisplayFormat->setCurrentIndex(0);
        updateSqlCode();
    } else {
        ui->comboDisplayFormat->addItem(tr("Custom"), "custom");
        ui->comboDisplayFormat->setCurrentIndex(ui->comboDisplayFormat->findData("custom"));
        ui->editDisplayFormat->setText(current_format);
    }
}

ColumnDisplayFormatDialog::~ColumnDisplayFormatDialog()
{
    delete ui;
}

QString ColumnDisplayFormatDialog::selectedDisplayFormat() const
{
    if(ui->comboDisplayFormat->currentData().toString() == "default")
        return QString();
    else
        return ui->editDisplayFormat->text();
}

void ColumnDisplayFormatDialog::updateSqlCode()
{
    QString format = ui->comboDisplayFormat->currentData().toString();
    if(format == "default")
        ui->editDisplayFormat->setText("`" + column_name + "`");
    else if(format == "lower")
        ui->editDisplayFormat->setText("lower(`" + column_name + "`)");
    else if(format == "upper")
        ui->editDisplayFormat->setText("upper(`" + column_name + "`)");
    else if(format == "epoch")
        ui->editDisplayFormat->setText("datetime(`" + column_name + "`, 'unixepoch')");
    else if(format == "julian")
        ui->editDisplayFormat->setText("datetime(`" + column_name + "`)");
    else if(format == "round")
        ui->editDisplayFormat->setText("round(`" + column_name + "`)");
}