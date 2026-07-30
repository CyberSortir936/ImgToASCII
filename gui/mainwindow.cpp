#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->CustomBack->setEnabled(false);
    ui->CustomAccent->setEnabled(false);

    ui->PixelSlider->setMinimum(2);
    ui->PixelSlider->setMaximum(32);
    ui->PixelSlider->setValue(8);
    ui->PixelRatio->setText("8");

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isValidColor(QString hexColor){
    if (hexColor[0] != '#')
        return false;

    if (!(hexColor.length() == 4 or hexColor.length() == 7))
        return false;

    for (int i = 1; i < hexColor.length(); i++)
        if (!((hexColor[i] >= '0' && hexColor[i] <= '9')
              || (hexColor[i] >= 'a' && hexColor[i] <= 'f')
              || (hexColor[i] >= 'A' || hexColor[i] <= 'F')))
            return false;

    return true;
}

void MainWindow::setInputPath(QString inputPath){
    this->inputPath = inputPath;
}
void MainWindow::setOutputPath(QString outputPath){
    this->outputPath = outputPath;
}
void MainWindow::setPixelScale(int pixelScale){
    this->pixelScale = pixelScale;
}
void MainWindow::setInverted(bool isInverted){
    this->isInverted = isInverted;
}
void MainWindow::setEdges(bool isEdges){
    this->isEdges = isEdges;
}
void MainWindow::setColorScheme(QString colorScheme){
    this->colorScheme = colorScheme;
}
void MainWindow::setAccentColor(int accentColor){
    this->accentColor = accentColor;
}
void MainWindow::setCustomBack(QString customBack){
    if(isValidColor(customBack)){
        this->customBack = customBack;
    }
}
void MainWindow::setCustomAccent(QString customAccent){
    if(isValidColor(customAccent)){
        this->customAccent = customAccent;
    }
}

void MainWindow::setCustomColor(bool isCustomColor){
    this->isCustomColor = isCustomColor;
}

QString MainWindow::getInputPath(){
    return this->inputPath;
}
QString MainWindow::getOutputPath(){
    return this->outputPath;
}
int MainWindow::getPixelScale(){
    return this->pixelScale;
}
bool MainWindow::getInverted(){
    return this->isInverted;
}
bool MainWindow::getEdges(){
    return this->isEdges;
}
QString MainWindow::getColorScheme(){
    return this->colorScheme;
}
int MainWindow::getAccentColor(){
    return this->accentColor;
}
QString MainWindow::getCustomBack(){
    return this->customBack;
}
QString MainWindow::getCustomAccent(){
    return this->customAccent;
}

bool MainWindow::getCustomColor(){
    return this->isCustomColor;
}

void MainWindow::on_BrowseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select File"),
                                                    QCoreApplication::applicationDirPath(),
                                                    tr("Image Files (*.jpg *.png *.bmp)"));

    if(fileName.isNull() || fileName.isEmpty()){
        qDebug() << "No File opened";
        return;
    }

    qDebug() << "Filename: " << fileName;

    setInputPath(fileName);
    ui->filePath->setText(fileName);
}


void MainWindow::on_ColorSchemeDropDown_activated(int index)
{
    //Gruvbox, Everforest, Nord, Kanagawa, Catppuccin, Dracula, Custom
    switch (index) {
    case 0:
        setColorScheme("Gruvbox");
        break;
    case 1:
        setColorScheme("Everforest");
        break;
    case 2:
        setColorScheme("Nord");
        break;
    case 3:
        setColorScheme("Kanagawa");
        break;
    case 4:
        setColorScheme("Catppuccin");
        break;
    case 5:
        setColorScheme("Dracula");
        break;
    case 6:
        setColorScheme("Custom");
        setCustomColor(true);

        ui->CustomBack->setEnabled(true);
        ui->CustomAccent->setEnabled(true);
        ui->AccentDropDown->setEnabled(false);
        return;
    default:
        break;
    }

    setCustomColor(false);
    ui->CustomBack->setEnabled(false);
    ui->CustomAccent->setEnabled(false);
    ui->AccentDropDown->setEnabled(true);
}


void MainWindow::on_PixelSlider_valueChanged(int value)
{
    setPixelScale(value);
    ui->PixelRatio->setText(QString::number(value));
}

void MainWindow::on_filePath_textChanged(const QString &arg1)
{
    setInputPath(arg1);
}


void MainWindow::on_PixelRatio_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok, 10);

    if(value > 32) value = 32;
    else if(value < 2) value = 2;

    setPixelScale(value);
    ui->PixelSlider->setValue(value);

    qDebug() << getPixelScale();
}


void MainWindow::on_CustomBack_textChanged(const QString &arg1)
{
    setCustomBack(arg1);
}


void MainWindow::on_CustomAccent_textChanged(const QString &arg1)
{
    setCustomAccent(arg1);
}


void MainWindow::on_InvertCheck_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1 == 2) setInverted(true);
    else setInverted(false);
}


void MainWindow::on_EdgesCheck_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1 == 2) setEdges(true);
    else setEdges(false);
}


void MainWindow::on_SaveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File As"),
                                                    QCoreApplication::applicationDirPath(),
                                                    tr("Image Files (*.jpg *.png *.bmp)"));

    setOutputPath(fileName);
    qDebug() << "Filename: " << fileName;
}


void MainWindow::on_AccentDropDown_currentIndexChanged(int index)
{
    setAccentColor(index);
}

