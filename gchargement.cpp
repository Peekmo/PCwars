#include "gchargement.h"

GChargement::GChargement(QWidget* parent): sonNbTimeOut(0)
{
    // Définition du fond
    QLabel *sonFondAffiche = new QLabel(this);
    sonFondAffiche->setPixmap(QPixmap("images/titre.jpg"));
    sonFondAffiche->setGeometry(0,0,700,500);

    this->setParent(parent);
    this->setFixedSize(700, 500);
    this->setStyleSheet("QProgressBar { border: 2px solid black; border-radius: 5px; } QProgressBar::chunk { background-color: #05B8CC; width: 20px; }");

    sonTimer = new QTimer(this);

    QLabel *leTexte = new QLabel(this);
    leTexte->setText("Chargement en cours ...");
    leTexte->setStyleSheet("color:black; font-size:15px; text-align:center;");
    leTexte->setGeometry(275, 350, 200, 30);

    sonChargement = new QProgressBar(this);
    sonChargement->setMaximum(100);
    sonChargement->setOrientation(Qt::Horizontal);
    sonChargement->setGeometry(150, 400, 400, 30);
    sonChargement->setTextVisible(false);

    QObject::connect(sonTimer, SIGNAL(timeout()), this, SLOT(augmenter()));
}

void GChargement::augmenter()
{
    sonNbTimeOut++;
    sonChargement->setValue(sonNbTimeOut);

    if (sonNbTimeOut == 110)
        emit (finChargement());
}

void GChargement::startTimer()
{
    sonTimer->start(50);
}
