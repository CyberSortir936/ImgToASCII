#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setInputPath(QString inputPath);
    void setOutputPath(QString outputPath);
    void setPixelScale(int pixelScale);
    void setInverted(bool isInverted);
    void setEdges(bool isEdges);
    void setColorScheme(QString colorScheme);
    void setAccentColor(int accentColor);
    void setCustomBack(QString customBack);
    void setCustomAccent(QString customAccent);
    void setCustomColor(bool isCustomColor);

    QString getInputPath();
    QString getOutputPath();
    int getPixelScale();
    bool getInverted();
    bool getEdges();
    QString getColorScheme();
    int getAccentColor();
    QString getCustomBack();
    QString getCustomAccent();
    bool getCustomColor();

    bool isValidColor(QString hexColor);

private slots:
    void on_BrowseButton_clicked();

    void on_ColorSchemeDropDown_activated(int index);

    void on_PixelSlider_valueChanged(int value);

    void on_filePath_textChanged(const QString &arg1);

    void on_PixelRatio_textChanged(const QString &arg1);

    void on_CustomBack_textChanged(const QString &arg1);

    void on_CustomAccent_textChanged(const QString &arg1);

    void on_InvertCheck_checkStateChanged(const Qt::CheckState &arg1);

    void on_EdgesCheck_checkStateChanged(const Qt::CheckState &arg1);

    void on_SaveButton_clicked();

private:
    Ui::MainWindow *ui;

    QString inputPath;
    QString outputPath;

    int pixelScale = 8;
    bool isInverted = false;
    bool isEdges = false;

    QString colorScheme;
    int accentColor = 0;

    bool isCustomColor = false;

    QString customBack = "#000000";
    QString customAccent = "#FFFFFF";
};
#endif // MAINWINDOW_H
