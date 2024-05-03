#include "ttkansplashscreen.h"

#include <QTimer>
#include <QPainter>
#include <QMouseEvent>

TTKAnSplashScreen::TTKAnSplashScreen(QWidget *parent)
    : QWidget(parent),
      m_mainWidget(nullptr)
{
    initialize();
}

TTKAnSplashScreen::~TTKAnSplashScreen()
{
    delete m_loadTimer;
    delete m_countTimer;
}

void TTKAnSplashScreen::setWidget(QWidget *main)
{
    m_mainWidget = main;
}

QWidget *TTKAnSplashScreen::widget()
{
    return m_mainWidget;
}

void TTKAnSplashScreen::setLoadText(const QString &title)
{
    if(!title.isEmpty())
    {
        m_textLabel->setText(title);
    }
}

void TTKAnSplashScreen::setLoadCount(int count)
{
    if(m_count != count)
    {
        m_count = count;
    }
    m_numLabel->setText(QString::number(m_count));
}

void TTKAnSplashScreen::start()
{
    m_countTimer->start();
    m_loadTimer->start();
    show();
}

void TTKAnSplashScreen::initialize()
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_loadTimer = new QTimer(this);
    connect(m_loadTimer, SIGNAL(timeout()), SLOT(update()));
    m_loadTimer->setInterval(5 * TTK_DN_MS);

    m_countTimer = new QTimer(this);
    connect(m_countTimer, SIGNAL(timeout()), SLOT(countTimeout()));
    m_countTimer->setInterval(TTK_DN_S2MS);

    m_dig = 0;
    m_count = 6;

    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setSpacing(0);
    m_gridLayout->setContentsMargins(11, 11, 11, 11);

    m_numLabel = new QLabel(this);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_numLabel->sizePolicy().hasHeightForWidth());

    m_numLabel->setText(QString::number(m_count));
    m_numLabel->setSizePolicy(sizePolicy);
    m_numLabel->setAlignment(Qt::AlignCenter);
    m_numLabel->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
                                                "font:75 50pt \"\346\245\267\344\275\223\";\n"
                                                "background-color:rgb(55, 55, 55);"));

    m_textLabel = new QLabel(this);
    m_textLabel->setText("Loading");
    m_textLabel->setMinimumSize(0,40);
    m_textLabel->setMaximumHeight(40);
    m_textLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    m_textLabel->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
                                                 "font:75 14pt \"\346\245\267\344\275\223\";\n"
                                                 "background-color:rgb(55, 55, 55);"));

    m_gridLayout->setContentsMargins(70, 70, 70, 70);
    m_gridLayout->addWidget(m_numLabel, 1, 0, 1, 1);
    m_gridLayout->addWidget(m_textLabel, 2, 0, 1, 1);
    setLayout(m_gridLayout);

    setStyleSheet("QLabel{ color:rgb(255,255,255); font:75 50pt \"\346\245\267\344\275\223\"; background-color:rgb(55,55,55) }");

    resize(300, 300);
}

void TTKAnSplashScreen::mousePressEvent(QMouseEvent *event)
{
    m_mousePos = QtMouseGlobalPos(event) - pos();
}

void TTKAnSplashScreen::mouseMoveEvent(QMouseEvent *event)
{
    move(QtMouseGlobalPos(event) - m_mousePos);
}

void TTKAnSplashScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap pix;
    pix.load(":/res/lb_loading");
    painter.translate(m_w / 2, m_h / 2);
    painter.rotate(m_dig);
    painter.translate(-m_w / 2, -m_h / 2);
    painter.drawPixmap(0, 0, m_w, m_h, pix);

    m_dig++;
    if(m_dig >= 360)
    {
        m_dig = 0;
    }
}

void TTKAnSplashScreen::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    m_w = width();
    m_h = height();
}

void TTKAnSplashScreen::countTimeout()
{
    m_count--;
    m_numLabel->setText(QString::number(m_count));

    if(m_count <= 0)
    {
        Q_EMIT finish();

        if(m_loadTimer->isActive())
        {
            m_loadTimer->stop();
        }

        if(m_countTimer->isActive())
        {
            m_countTimer->stop();
        }

        close();
        if(m_mainWidget)
        {
            m_mainWidget->show();
        }
    }
}
