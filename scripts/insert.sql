USE `UpravljanjeGradilistima`;

DELIMITER $$

INSERT INTO Gradiliste (Naziv, Adresa) VALUES
    ('Studenjak', 'Tosin bunar 143 Beograd'),
    ('Dimitrijala', 'Dimitrija Tucovica 50 Beograd'),
    ('Dalmatinska', 'Dalmatinska 123 Beograd'),
    ('Senjak', 'Nova ulica 4 Beograd')
$$

INSERT INTO Gradiliste (Naziv, Adresa, Status) VALUES
    ('Hotel', 'Cvijiceva 60 Beograd', 'pauza')
$$

UPDATE Gradiliste
SET Status = 'zavrseno'
WHERE Naziv = 'Senjak'
$$

DELETE FROM Gradiliste
WHERE Naziv = 'Dalmatinska'
$$

INSERT INTO Firma (Ime, Adresa, Telefon) VALUES
    ('Energogroup', 'Bulevar Milutina Milankovica 158 Beograd', '0641234567'),
    ('Energoprojekt', 'Dimitrija Tucovica 150 Beograd', '011521521'),
    ('Mostogradnja', 'Cetinjstka 3 Beograd', '0659876543'),
    ('Crna trava', 'Neka druga ulica 54 Beograd', '063000111')
$$


INSERT INTO Radnik (Ime, Prezime, idFirme, Pozicija, Telefon, CenaPoSatu) VALUES
    ('Marko', 'Markovic', 1, 'tesar', '0641234567', 350),
    ('Pera', 'Peric', 2, 'zidar', '0641234567', null),
    ('Ana', 'Marinkovic', 3, 'vozac', '0641234567', 260),
    ('Dusan', 'Petrovic', 1, 'geometar', '0641234567', 400)
    -- ('Sasa', 'Peric', 3, 'vozac', '0641234567', 200) triger sprecava unos
$$

INSERT INTO SatnicaRadnika (idRadnika, idGradilista, Datum, brojSati) VALUES
    (1, 1, null, 5),
    (1, 2, null, 3),
    (1, 1, '2017-12-9', 8),
    (1, 2, '2017-11-8', 7),
    (2, 4, '2017-11-30', 8),
    (2, 4, '2017-11-29', 8),
    (2, 4, '2017-11-28', 8),
    (3, 2, '2017-11-30', 4),
    (3, 2, '2017-11-29', 7)
$$

INSERT INTO Masina (Naziv, Proizvodjac, PotrosnjaGoriva, CenaPoSatu) VALUES
    ('Busilica', 'Cat', null, 350),
    ('Bager', 'Cat', null, 500)
$$

INSERT INTO SatnicaMasine (idMasine, idGradilista, Datum, brojSati) VALUES
    (1, 1, null, 5),
    (1, 2, null, 3),
    (2, 1, '2017-12-9', 8),
    (2, 2, '2017-11-8', 7)
$$

INSERT INTO FazaRadova (Naziv) VALUES
    ('Pripremni radovi'),
    ('Iskop'),
    ('Temelj'),
    ('Prvi sprat'),
    ('Drugi sprat'),
    ('Treci sprat'),
    ('Fasada')
$$

INSERT INTO VrstaRadova (Naziv) VALUES
    ('Armiracki radovi'),
    ('Tesarski radovi'),
    ('Betonski radovi'),
    ('Zemljani radovi'),
    ('Geodetski radovi')
$$

INSERT INTO RadoviNaGradilistu (idGradilista, idFazeRadova, idVrsteRadova, Datum) VALUES
    (1, 2, 4, null),
    (1, 2, 4, '2017-12-9'),
    (2, 4, 3, '2017-12-9'),
    (2, 4, 3, '2017-11-8'),
    (5, 7, 5, '2016-7-7'),
    (5, 7, 5, '2016-7-8')
$$

INSERT INTO Trosak (Naziv, CenaPoDanu) VALUES
    ('Iznajmljivanje kontejnera', 4000),
    ('Iznajmljivanje krana', 15000),
    ('Iznajmljivanje mesalice', 11000),
    ('Pumpa za beton', 8500)
$$

INSERT INTO TrosakGradiliste (idGradilista, idTroska, DatumPocetka, DatumZavrsetka) VALUES
    (1, 1, null, null),
    (1, 2, null, null),
    (2, 1, '2017-10-9', '2017-12-5'),
    (2, 4, '2017-10-20', null)
$$

INSERT INTO Proizvod (Naziv, Cena, Proizvodjac, Napomena) VALUES
    ('Cement', 700, 'Titan', '50kg pakovanje'),
    ('Agregat', 2000, 'Titan', 'kubik')
$$

INSERT INTO Nabavka (idGradilista, idProizvoda, Kolicina, Datum, Napomena) VALUES
    (1, 1, 3, null, 'hitna dostava'),
    (1, 1, 1, '2017-10-9', null),
    (2, 2, 2, '2017-12-5', null),
    (2, 2, 5, null, 'Super cena!')
$$


DELIMITER ;
