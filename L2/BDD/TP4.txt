1. 

create table pers(id_pers serial primary key, nom_pers varchar(25) not null, prenom_pers varchar(25) not null, date_nais date not null, date_deces date, nationalite varchar(30));
create table edit(id_edit serial primary key, nom_edit varchar(50), pays varchar(50));
create table cd(id_cd serial not null primary key, titre_cd varchar(20) not null,  id_edition integer references edit(id_edit), note_art integer, note_tech integer, nom_distrib varchar(40));
create table enr
(
    id_cd integer references cd(id_cd),
    id_enr serial not null,
    titre_enr varchar(50),
    duree_enr int,
    annee_enr integer check(annee_enr between 1900 and 2150),
    lieu_enr varchar(40),
    cond_enr varchar(40) check(cond_enr in ('studio','live','public','acoustic')),
    primary key(id_cd,id_enr)
);

create table interp
(
    id_cd integer,
    id_enr integer,
    id_interp integer references pers(id_pers),
    instrument varchar(40),
	foreign key(id_cd, id_enr) references enr(id_cd,id_enr),
    primary key(id_cd,id_enr,id_interp,instrument)
);

create table leader
(
    id_cd integer references cd(id_cd) not null,
    id_leader integer references pers(id_pers) not null,
    primary key(id_cd,id_leader)
);

create table compo
(
    id_cd integer not null,
    id_enr integer not null,
    id_compositeur integer references pers(id_pers) not null,
    foreign key(id_cd, id_enr) references enr(id_cd, id_enr),
    primary key(id_cd, id_enr, id_compositeur)
);


2.

select titre_enr from enr;
select nom_pers from pers where date(now()) - date_deces < 3650;
select titre_enr from enr where cond_enr == 'public' and lieu_enr in ('Chicago','Saint-Louis') and annee_enr > 1980;
select id_cd from enr where duree_enr = (select max(duree_enr) from enr where cond_enr in ('public','acoustic'));

3.
create table musique
(
    id_mus serial primary key,
    titre_mus varchar(30) not null,
    annee_mus int
);

update table set mus.titre_mus = enr.titre_enr;
