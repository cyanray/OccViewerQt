#include <OccViewerQt/SettingsDialog/SettingsDialog.h>

#include "ui_SettingsDialog.h"


namespace OccViewerQt
{
    SettingsDialog::SettingsDialog(QWidget* parent): QDialog(parent), m_ui(new Ui::SettingsDialog)
    {
        m_ui->setupUi(this);
    }

    SettingsDialog::~SettingsDialog()
    {
        delete m_ui;
    }


}



