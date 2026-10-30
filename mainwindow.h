#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 重写键盘事件
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    // 功能按钮
    void on_btnPercent_clicked();
    void on_btnCE_clicked();
    void on_btnClear_clicked();
    void on_btnBackspace_clicked();
    void on_btnReciprocal_clicked();
    void on_btnSquare_clicked();
    void on_btnSqrt_clicked();
    void on_btnAdd_clicked();
    void on_btnSub_clicked();
    void on_btnMul_clicked();
    void on_btnDiv_clicked();
    void on_btnNeg_clicked();
    void on_btnDot_clicked();
    void on_btnEqual_clicked();

    // 数字按钮 btnNum0~btnNum9
    void on_btnNum0_clicked();
    void on_btnNum1_clicked();
    void on_btnNum2_clicked();
    void on_btnNum3_clicked();
    void on_btnNum4_clicked();
    void on_btnNum5_clicked();
    void on_btnNum6_clicked();
    void on_btnNum7_clicked();
    void on_btnNum8_clicked();
    void on_btnNum9_clicked();

private:
    Ui::MainWindow *ui;

    // 计算器状态变量（写进实验报告）
    double      m_num1;         // 保存第一个操作数
    QString     m_op;           // 保存运算符 + - * /
    bool        m_waitNewNum;   // true=需要输入新数字（按完运算符/等于）
    bool        m_hasError;     // 错误标记：除零、负数开根号锁定输入

    void handleInput(QString key);  // 统一输入处理：鼠标、键盘都调用这个
    void clearAll();                // C：全部清空
    void clearEntry();              // CE：清空当前输入，保留算式
};
#endif // MAINWINDOW_H

