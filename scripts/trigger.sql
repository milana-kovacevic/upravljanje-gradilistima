USE `UpravljanjeGradilistima`;

DELIMITER $$


-- ------------------------------------------------------
-- Triger postavlja pocetni status gradilista na 'u pripremi'
-- ukoliko on nije postavljen
-- ------------------------------------------------------
DROP TRIGGER IF EXISTS `triger_biGradiliste` $$

create trigger triger_biGradiliste before insert on Gradiliste
for each row
begin
    declare msg VARCHAR(255);
    if (new.Status is null) then
        set new.Status = 'u pripremi';
    elseif (new.Status not in ('u pripremi', 'aktivno', 'pauza', 'zavrseno')) then
        set msg = 'Greska: Status gradilista mora da bude u pripremi, aktivno, pauza ili zavrseno.';
        SIGNAL sqlstate '45000' set message_text = msg;
    end if;
end $$

-- ------------------------------------------------------
-- Triger koji proverava da li je novi status gradilista 
-- u pripremi, aktivno, pauza ili zavrseno.
-- ------------------------------------------------------
DROP TRIGGER IF EXISTS `triger_buGradiliste` $$

create trigger triger_buGradiliste before update on Gradiliste
for each row
begin
    declare msg VARCHAR(255);
    if (new.Status is null) then
        set new.Status = 'u pripremi';
    elseif (new.Status not in ('u pripremi', 'aktivno', 'pauza', 'zavrseno')) then
        set msg = 'Greska: Status gradilista mora da bude u pripremi, aktivno, pauza ili zavrseno.';
        SIGNAL sqlstate '45000' set message_text = msg;
    end if;
end $$

-- -----------------------------------------------------
-- Triger proverava da li je cena usluga radnika po satu
-- u skladu sa zakonom
-- -----------------------------------------------------
DROP TRIGGER IF EXISTS `triger_biRadnik` $$

create trigger triger_biRadnik before insert on Radnik 
for each row
begin
    declare msg VARCHAR(255);
    declare minCena DECIMAL;
    set minCena = 250;
    if (new.CenaPoSatu is null) then
        set new.CenaPoSatu = minCena;
    elseif (new.CenaPoSatu < minCena) then
        set msg = 'Greska: Cena radnika po satu mora da bude bar 250 din.';
        SIGNAL sqlstate '45000' set message_text = msg;
    end if;
end $$

-- -----------------------------------------------------
-- Triger proverava da li je cena usluga radnika po satu
-- u skladu sa zakonom
-- -----------------------------------------------------
DROP TRIGGER IF EXISTS `triger_buRadnik` $$

create trigger triger_buRadnik before update on Radnik 
for each row
begin
    declare msg VARCHAR(255);
    declare minCena DECIMAL;
    set minCena = 250;
    if (new.CenaPoSatu is null) then
        set new.CenaPoSatu = minCena;
    elseif (new.CenaPoSatu < minCena) then
        set msg = 'Greska: Cena radnika po satu mora da bude bar 250 din.';
        SIGNAL sqlstate '45000' set message_text = msg;
    end if;
end $$

-- -----------------------------------------------------
-- Triger koji proverava da li je kolicina > 0 i postavlja
-- cenu na proizvod.cena * kolicina pri unosu u tabelu Nabavka
-- -----------------------------------------------------
DROP TRIGGER IF EXISTS `triger_biNabavka` $$

create trigger triger_biNabavka before insert on Nabavka
for each row
begin
    declare msg VARCHAR(255);
    if (new.Kolicina <= 0) then
        set msg = 'Greska: Kolicina mora da bude pozitivan broj.';
        SIGNAL sqlstate '45000' set message_text = msg;
    end if;
    set new.Cena = new.Kolicina * (select p.Cena
                                    from Proizvod p
                                    where p.idProizvoda = new.idProizvoda);
    if (new.Datum is null) then
        set new.Datum = curdate();
    end if;
end $$


-- -----------------------------------------------------
-- Triger postavlja datum na trenutni datum ukoliko on
-- nije postavljen pre unosa u tabelu RadoviNaGradilistu
-- -----------------------------------------------------
DROP TRIGGER IF EXISTS `triger_biRadoviNaGradilistu` $$

create trigger triger_biRadoviNaGradilistu before insert on RadoviNaGradilistu
for each row
begin
    if (new.Datum is null) then
        set new.Datum = curdate();
    end if;
end $$


-- -----------------------------------------------------
-- Triger postavlja datum na trenutni datum ukoliko on
-- nije postavljen pre unosa u tabelu SatnicaRadnika
-- -----------------------------------------------------
DROP TRIGGER IF EXISTS `triger_biSatnicaRadnika` $$

create trigger triger_biSatnicaRadnika before insert on SatnicaRadnika
for each row
begin
    if (new.Datum is null) then
        set new.Datum = curdate();
    end if;
end $$


-- -----------------------------------------------------
-- Triger postavlja datum na trenutni datum ukoliko on
-- nije postavljen pre unosa u tabelu SatnicaMasine
-- -----------------------------------------------------
DROP TRIGGER IF EXISTS `triger_biSatnicaMasine` $$

create trigger triger_biSatnicaMasine before insert on SatnicaMasine
for each row
begin
    if (new.Datum is null) then
        set new.Datum = curdate();
    end if;
end $$


-- -----------------------------------------------------
-- Triger postavlja datum na trenutni datum ukoliko on
-- nije postavljen pre unosa u tabelu TrosakGradiliste
-- -----------------------------------------------------
DROP TRIGGER IF EXISTS `triger_biTrosakGradiliste` $$

create trigger triger_biTrosakGradiliste before insert on TrosakGradiliste
for each row
begin
    if (new.DatumPocetka is null) then
        set new.DatumPocetka = curdate();
    end if;
end $$


-- -----------------------------------------------------
-- Triger postavlja status gradilista na 'aktivno' ukoliko
-- su se radovi desili u prethodnih 7 dana nakon 
-- unosa podataka u tabelu RadoviNaGradilistu
-- -----------------------------------------------------

DROP TRIGGER IF EXISTS `triger_aiRadoviNaGradilistu` $$

create trigger triger_aiRadoviNaGradilistu after insert on RadoviNaGradilistu
for each row
begin
    if (new.Datum > curdate() - 7) then
        update Gradiliste g
        set g.status = 'aktivno'
        where g.idGradilista = new.idGradilista;
    end if;
end $$


-- -----------------------------------------------------
-- Triger postavlja status gradilista na 'aktivno' ukoliko
-- je datum unete satnice u prethodnih 7 dana nakon unosa
-- u tabelu SatnicaRadnika
-- -----------------------------------------------------
DROP TRIGGER IF EXISTS `triger_aiSatnicaRadnika` $$

create trigger triger_aiSatnicaRadnika after insert on SatnicaRadnika
for each row
begin
  if (new.Datum > curdate() - 7) then
    update Gradiliste g
    set g.Status = 'aktivno'
    where g.idGradilista = new.idGradilista;
  end if;
end $$


-- -----------------------------------------------------
-- Triger postavlja status gradilista na 'aktivno' ukoliko
-- je datum unete satnice u prethodnih 7 dana nakon unosa
-- u tabelu SatnicaMasine
-- -----------------------------------------------------
DROP TRIGGER IF EXISTS `triger_aiSatnicaMasina` $$

create trigger triger_aiSatnicaMasina after insert on SatnicaMasine
for each row
begin
  if (new.Datum > curdate() - 7) then
    update Gradiliste g
    set g.status = 'aktivno'
    where g.idGradilista = new.idGradilista;
  end if;
end $$


DELIMITER ;
