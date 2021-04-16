/*
    Ohjelman kirjoittaja
    Nimi: Pyry Laine
    Opiskelijanro: 50282836
    GIT-käyttäjätunnus: smpyla
    Sähköposti: pyry.j.laine@tuni.fi

    Sairaala-projekti:
    Tämä ohjelma kuvastaa sairaalan potilastietojärjestelmää, joka  sisältää seuraavat ominaisuudet:

    enter: lisätään potilas tietokantaan.
    leave: päätetään potilaan hoitojakso.
    assign_staff: rekrytoidaan uusi hoitohenkilö.
    print_patient_info: tulostetaan tietyn potilaan tiedot(hoitojakson ajankohta, hoitajat ja lääkitys).
    print_care_periods: tulostetaan hoitajakohtaiset potilaat ja heidän hoitoaikansa.
    print_all_medicines: tulostaa sairaalassa käytössä olevat lääkkeet ja niiden käyttäjät.
    print_all_patients: tulostaa kaikki potilaat sairaalan historiassa ja heidän tietonsa.
    print_current_patients: tulostaa hoidossa olevat potilaat ja heidän tietonsa.

    Lisäksi ohjelma sisältää käyttöliittymän sekä mahdollisuudet päivämäärän muokkaamiseen.

*/

#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";


int main()
{
    Hospital* hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    delete hospital;
    return EXIT_SUCCESS;
}
