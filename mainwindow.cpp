#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(480,600);
    setWindowTitle("计算器");

    m_num1 = 0.0;
    m_op = "";
    m_waitNewNum = false;
    m_hasError = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnPercent_clicked(){ handleInput("%"); }
void MainWindow::on_btnCE_clicked(){ handleInput("CE"); }
void MainWindow::on_btnClear_clicked(){ handleInput("C"); }
void MainWindow::on_btnBackspace_clicked(){ handleInput("⌫"); }
void MainWindow::on_btnReciprocal_clicked(){ handleInput("1/x"); }
void MainWindow::on_btnSquare_clicked(){ handleInput("x²"); }
void MainWindow::on_btnSqrt_clicked(){ handleInput("²√x"); }
void MainWindow::on_btnAdd_clicked(){ handleInput("+"); }
void MainWindow::on_btnSub_clicked(){ handleInput("-"); }
void MainWindow::on_btnMul_clicked(){ handleInput("*"); }
void MainWindow::on_btnDiv_clicked(){ handleInput("/"); }
void MainWindow::on_btnNeg_clicked(){ handleInput("+/-"); }
void MainWindow::on_btnDot_clicked(){ handleInput("."); }
void MainWindow::on_btnEqual_clicked(){ handleInput("="); }

void MainWindow::on_btnNum0_clicked(){ handleInput("0"); }
void MainWindow::on_btnNum1_clicked(){ handleInput("1"); }
void MainWindow::on_btnNum2_clicked(){ handleInput("2"); }
void MainWindow::on_btnNum3_clicked(){ handleInput("3"); }
void MainWindow::on_btnNum4_clicked(){ handleInput("4"); }
void MainWindow::on_btnNum5_clicked(){ handleInput("5"); }
void MainWindow::on_btnNum6_clicked(){ handleInput("6"); }
void MainWindow::on_btnNum7_clicked(){ handleInput("7"); }
void MainWindow::on_btnNum8_clicked(){ handleInput("8"); }
void MainWindow::on_btnNum9_clicked(){ handleInput("9"); }

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString key;
    switch (event->key())
    {
    case Qt::Key_0: key="0";break;
    case Qt::Key_1: key="1";break;
    case Qt::Key_2: key="2";break;
    case Qt::Key_3: key="3";break;
    case Qt::Key_4: key="4";break;
    case Qt::Key_5: key="5";break;
    case Qt::Key_6: key="6";break;
    case Qt::Key_7: key="7";break;
    case Qt::Key_8: key="8";break;
    case Qt::Key_9: key="9";break;
    case Qt::Key_Period: key=".";break;
    case Qt::Key_Plus: key="+";break;
    case Qt::Key_Minus: key="-";break;
    case Qt::Key_Asterisk: key="*";break;
    case Qt::Key_Slash: key="/";break;
    case Qt::Key_Enter:
    case Qt::Key_Return: key="=";break;
    case Qt::Key_Backspace: key="⌫";break;
    case Qt::Key_Escape: key="C";break;
    default:
        QMainWindow::keyPressEvent(event);
        return;
    }
    handleInput(key);
}

void MainWindow::handleInput(QString key)
{
    if(m_hasError && key != "C")
        return;

    QString disp = ui->labDisplay->text();

    if(key == "C")
    {
        clearAll();
        return;
    }
    if(key == "CE")
    {
        clearEntry();
        return;
    }
    if(key == "⌫")
    {
        if(m_waitNewNum) return;
        if(disp.size() <= 1)
            ui->labDisplay->setText("0");
        else
            ui->labDisplay->setText(disp.left(disp.length()-1));
        return;
    }

    if(key == "%" || key == "1/x" || key == "x²" || key == "²√x" || key == "+/-")
    {
        double val = disp.toDouble();
        double res = val;
        if(key == "%")
        {
            res = val / 100.0;
        }
        else if(key == "1/x")
        {
            if(fabs(val) < 1e-9)
            {
                ui->labDisplay->setText("错误");
                m_hasError = true;
                return;
            }
            res = 1.0 / val;
        }
        else if(key == "x²")
        {
            res = val * val;
        }
        else if(key == "²√x")
        {
            if(val < 0)
            {
                ui->labDisplay->setText("错误");
                m_hasError = true;
                return;
            }
            res = sqrt(val);
        }
        else if(key == "+/-")
        {
            res = -val;
        }
        ui->labDisplay->setText(QString::number(res));
        m_waitNewNum = true;
        return;
    }

    if(key == "+" || key == "-" || key == "*" || key == "/")
    {
        m_num1 = disp.toDouble();
        m_op = key;
        m_waitNewNum = true;
        return;
    }

    if(key == "=")
    {
        if(m_op.isEmpty()) return;
        double num2 = disp.toDouble();
        double res = 0;
        if(m_op == "+")
            res = m_num1 + num2;
        else if(m_op == "-")
            res = m_num1 - num2;
        else if(m_op == "*")
            res = m_num1 * num2;
        else if(m_op == "/")
        {
            if(fabs(num2) < 1e-9)
            {
                ui->labDisplay->setText("除零错误");
                m_hasError = true;
                m_op = "";
                return;
            }
            res = m_num1 / num2;
        }
        ui->labDisplay->setText(QString::number(res));
        m_op = "";
        m_waitNewNum = true;
        return;
    }

    if(key == "." || (key >= "0" && key <= "9"))
    {
        if(m_waitNewNum)
        {
            disp = "";
            m_waitNewNum = false;
        }
        if(key == "." && disp.contains("."))
            return;

        if(disp == "0" && key != ".")
            disp = "";
        disp += key;
        ui->labDisplay->setText(disp);
        return;
    }
}

void MainWindow::clearAll()
{
    ui->labDisplay->setText("0");
    m_num1 = 0.0;
    m_op = "";
    m_waitNewNum = false;
    m_hasError = false;
}

void MainWindow::clearEntry()
{
    ui->labDisplay->setText("0");
    m_waitNewNum = false;
}
