#ifndef GCHARGEMENT_H
#define GCHARGEMENT_H
/**
 * \file          gchargement.cpp
 * \author    Anceau Axel - Brangier Simon
 * \version   1.0
 * \date       1 Mai 2012
 * \brief       Classe contenant les parametres de la fenetre de chargement
 */
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>

class GChargement : public QWidget
{
    Q_OBJECT

private:
    int sonNbTimeOut;
    QProgressBar *sonChargement;
    QTimer *sonTimer;

public slots:
    /**
      * \brief      Slot de remplissage de la barre de progression
      */
    void augmenter();

signals:
    /**
      * \brief      Signal de fin du chargement
      */
    void finChargement();

public:
    /**
      * \brief      Constructeur de la fenêtre de chargement
      * \param parent
      */
    GChargement(QWidget*);

    /**
      * \brief      Methode de demarrage du timer
      */
    void startTimer();
};

#endif // GCHARGEMENT_H
