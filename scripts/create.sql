-- -----------------------------------------------------
-- Schema UpravljanjeGradilistima
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `UpravljanjeGradilistima` ;

-- -----------------------------------------------------
-- Schema UpravljanjeGradilistima
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `UpravljanjeGradilistima` DEFAULT CHARACTER SET utf8 ;
USE `UpravljanjeGradilistima` ;


-- -----------------------------------------------------
-- Table `Gradiliste`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Gradiliste` ;

CREATE TABLE IF NOT EXISTS `UpravljanjeGradilistima`.`Gradiliste` (
  `idGradilista` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Naziv` VARCHAR(45) NULL,
  `Adresa` VARCHAR(45) NULL,
  `Status` VARCHAR(45) NULL,
  INDEX `fk_Gradiliste_idx` (`idGradilista` ASC),
  PRIMARY KEY (`idGradilista`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Firma`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Firma` ;

CREATE TABLE IF NOT EXISTS `Firma` (
  `idFirme` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Ime` VARCHAR(45) NOT NULL,
  `Adresa` VARCHAR(45) NULL,
  `Telefon` VARCHAR(45) NULL,
  PRIMARY KEY (`idFirme`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Radnik`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Radnik` ;

CREATE TABLE IF NOT EXISTS `Radnik` (
  `idRadnika` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Ime` VARCHAR(45) NOT NULL,
  `Prezime` VARCHAR(45) NOT NULL,
  `idFirme` INT UNSIGNED NOT NULL,
  `Pozicija` VARCHAR(45) NULL,
  `Telefon` VARCHAR(45) NULL,
  `CenaPoSatu` DECIMAL UNSIGNED NOT NULL,
  INDEX `fk_Radnik_idx` (`idRadnika` ASC),
  PRIMARY KEY (`idRadnika`),
  CONSTRAINT `idFirme`
    FOREIGN KEY (`idFirme`)
    REFERENCES `Firma` (`idFirme`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `SatnicaRadnika`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `SatnicaRadnika` ;

CREATE TABLE IF NOT EXISTS `SatnicaRadnika` (
  `idRadnika` INT UNSIGNED NOT NULL,
  `idGradilista` INT UNSIGNED NOT NULL,
  `Datum` DATE NOT NULL,
  `BrojSati` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`idRadnika`, `idGradilista`, `Datum`),
  CONSTRAINT `idGradilista`
    FOREIGN KEY (`idGradilista`)
    REFERENCES `Gradiliste` (`idGradilista`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `idRadnika`
    FOREIGN KEY (`idRadnika`)
    REFERENCES `Radnik` (`idRadnika`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `Masina`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Masina` ;

CREATE TABLE IF NOT EXISTS `Masina` (
  `idMasine` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Naziv` VARCHAR(45) NOT NULL,
  `Proizvodjac` VARCHAR(45) NULL,
  `PotrosnjaGoriva` DECIMAL UNSIGNED NULL,
  `CenaPoSatu` DECIMAL UNSIGNED NOT NULL,
  PRIMARY KEY (`idMasine`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `SatnicaMasine`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `SatnicaMasine` ;

CREATE TABLE IF NOT EXISTS `SatnicaMasine` (
  `idMasine` INT UNSIGNED NOT NULL,
  `idGradilista` INT UNSIGNED NOT NULL,
  `Datum` DATE NOT NULL,
  `BrojSati` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`idMasine`, `idGradilista`, `Datum`),
  CONSTRAINT `fk_idMasine`
    FOREIGN KEY (`idMasine`)
    REFERENCES `Masina` (`idMasine`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_idGradilista`
    FOREIGN KEY (`idGradilista`)
    REFERENCES `Gradiliste` (`idGradilista`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FazaRadova`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FazaRadova` ;

CREATE TABLE IF NOT EXISTS `FazaRadova` (
  `idFazeRadova` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Naziv` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idFazeRadova`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `VrstaRadova`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `VrstaRadova` ;

CREATE TABLE IF NOT EXISTS `VrstaRadova` (
  `idVrsteRadova` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Naziv` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`idVrsteRadova`))
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `RadoviNaGradilistu`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `RadoviNaGradilistu` ;

CREATE TABLE IF NOT EXISTS `RadoviNaGradilistu` (
  `idGradilista` INT UNSIGNED NOT NULL,
  `idVrsteRadova` INT UNSIGNED NOT NULL,
  `idFazeRadova` INT UNSIGNED NOT NULL,
  `Datum` DATE NOT NULL,
  CONSTRAINT `fk_idGradilista_2`
    FOREIGN KEY (`idGradilista`)
    REFERENCES `Gradiliste` (`idGradilista`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `idVrsteRadova`
    FOREIGN KEY (`idVrsteRadova`)
    REFERENCES `VrstaRadova` (`idVrsteRadova`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `idFazeRadova`
    FOREIGN KEY (`idFazeRadova`)
    REFERENCES `FazaRadova` (`idFazeRadova`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Trosak`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Trosak` ;

CREATE TABLE IF NOT EXISTS `Trosak` (
  `idTroska` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Naziv` VARCHAR(45) NOT NULL,
  `CenaPoDanu` DECIMAL UNSIGNED NOT NULL,
  PRIMARY KEY (`idTroska`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `TrosakGradiliste`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `TrosakGradiliste` ;

CREATE TABLE IF NOT EXISTS `TrosakGradiliste` (
  `idGradilista` INT UNSIGNED NOT NULL,
  `idTroska` INT UNSIGNED NOT NULL,
  `DatumPocetka` DATE NOT NULL,
  `DatumZavrsetka` DATE NULL,
  `Napomena` TINYBLOB NULL,
  PRIMARY KEY (`idGradilista`, `DatumPocetka`, `idTroska`),
  CONSTRAINT `fk_idGradilista_3`
    FOREIGN KEY (`idGradilista`)
    REFERENCES `Gradiliste` (`idGradilista`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_TrosakGradiliste`
    FOREIGN KEY (`idTroska`)
    REFERENCES `Trosak` (`idTroska`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Proizvod`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Proizvod` ;

CREATE TABLE IF NOT EXISTS `Proizvod` (
  `idProizvoda` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `Naziv` VARCHAR(45) NOT NULL,
  `Cena` DECIMAL UNSIGNED NOT NULL,
  `Proizvodjac` VARCHAR(45) NULL,
  `Napomena` TINYBLOB NULL,
  PRIMARY KEY (`idProizvoda`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Nabavka`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Nabavka` ;

CREATE TABLE IF NOT EXISTS `Nabavka` (
  `idGradilista` INT UNSIGNED NOT NULL,
  `idProizvoda` INT UNSIGNED NOT NULL,
  `Kolicina` INT UNSIGNED NOT NULL,
  `Cena` DECIMAL UNSIGNED NULL,
  `Datum` DATE NULL,
  `Napomena` TINYBLOB NULL,
  CONSTRAINT `fk_idGradilista_4`
    FOREIGN KEY (`idGradilista`)
    REFERENCES `Gradiliste` (`idGradilista`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `idProizvoda`
    FOREIGN KEY (`idProizvoda`)
    REFERENCES `Proizvod` (`idProizvoda`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;
