-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.0.77-community-nt


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema warbugs
--

CREATE DATABASE IF NOT EXISTS warbugs;
USE warbugs;

--
-- Definition of table `bolsa`
--

DROP TABLE IF EXISTS `bolsa`;
CREATE TABLE `bolsa` (
  `BSID` int(11) NOT NULL,
  `BSX` float default NULL,
  `BSY` float default NULL,
  `BSZ` float default NULL,
  `CNID` int(11) default NULL,
  PRIMARY KEY  (`BSID`),
  KEY `CNID` (`CNID`),
  CONSTRAINT `bolsa_ibfk_1` FOREIGN KEY (`CNID`) REFERENCES `cenario` (`CNID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `bolsa`
--

/*!40000 ALTER TABLE `bolsa` DISABLE KEYS */;
/*!40000 ALTER TABLE `bolsa` ENABLE KEYS */;


--
-- Definition of table `cenario`
--

DROP TABLE IF EXISTS `cenario`;
CREATE TABLE `cenario` (
  `CNID` int(11) NOT NULL,
  `CNNOME` varchar(30) default NULL,
  `CNIDMODELO` int(11) default NULL,
  `CNIDTEXTURA` int(11) default NULL,
  PRIMARY KEY  (`CNID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `cenario`
--

/*!40000 ALTER TABLE `cenario` DISABLE KEYS */;
INSERT INTO `cenario` (`CNID`,`CNNOME`,`CNIDMODELO`,`CNIDTEXTURA`) VALUES 
 (1,'Cenario1',1,1),
 (2,'Cenario2',2,2);
/*!40000 ALTER TABLE `cenario` ENABLE KEYS */;


--
-- Definition of table `item_relacional`
--

DROP TABLE IF EXISTS `item_relacional`;
CREATE TABLE `item_relacional` (
  `IRVALBONUS1` int(11) default '0',
  `IRPRECO` int(11) default '0',
  `IRVALBONUS7` int(11) default '0',
  `IRVALBONUS6` int(11) default '0',
  `IRVALBONUS5` int(11) default '0',
  `IRVALBONUS4` int(11) default '0',
  `IRVALBONUS3` int(11) default '0',
  `IRVALBONUS2` int(11) default '0',
  `ITID` int(11) default NULL,
  `PGID` int(11) default NULL,
  `BSID` int(11) default NULL,
  KEY `ITID` (`ITID`),
  KEY `PGID` (`PGID`),
  KEY `BSID` (`BSID`),
  CONSTRAINT `item_relacional_ibfk_1` FOREIGN KEY (`ITID`) REFERENCES `itembase` (`ITID`),
  CONSTRAINT `item_relacional_ibfk_2` FOREIGN KEY (`PGID`) REFERENCES `personagem` (`PGID`),
  CONSTRAINT `item_relacional_ibfk_3` FOREIGN KEY (`BSID`) REFERENCES `bolsa` (`BSID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `item_relacional`
--

/*!40000 ALTER TABLE `item_relacional` DISABLE KEYS */;
/*!40000 ALTER TABLE `item_relacional` ENABLE KEYS */;


--
-- Definition of table `itembase`
--

DROP TABLE IF EXISTS `itembase`;
CREATE TABLE `itembase` (
  `ITID` int(11) NOT NULL,
  `ITNIVELMAGICO` int(11) default NULL,
  `ITDURABILIDADE` int(11) default NULL,
  `ITNOME` varchar(30) default NULL,
  `ITDESCRICAO` varchar(200) default NULL,
  `ITALCANCE` int(11) default NULL,
  `ITVELOCIDADE` int(11) default NULL,
  `ITDROPAVEL` tinyint(1) default NULL,
  `ITRACA` int(11) default NULL,
  `ITDANOMAX` int(11) default NULL,
  `ITDANOMIN` int(11) default NULL,
  `ITMODIFICADOR` int(11) default NULL,
  `ITVALOR` int(11) default NULL,
  `ITDEFESA` int(11) default NULL,
  `ITISTEMP` tinyint(1) default NULL,
  `ITDURACAO` int(11) default NULL,
  `ITTIPO` int(11) default NULL,
  `ITLEALARANHA` int(11) default NULL,
  `ITLEALESCORPIAO` int(11) default NULL,
  `ITLEALLOUVA` int(11) default NULL,
  `ITLEALVESPA` int(11) default NULL,
  `ITLEALBESOURO` int(11) default NULL,
  `ITIDMODELO` int(11) default NULL,
  `ITIDTEXTURA` int(11) default NULL,
  `ITTIPOUSO` int(11) default NULL,
  `ITPRECO` int(11) default NULL,
  `ITIDTIPOITEM` int(11) default NULL,
  `ITIDHUD` int(11) default NULL,
  PRIMARY KEY  (`ITID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `itembase`
--

/*!40000 ALTER TABLE `itembase` DISABLE KEYS */;
INSERT INTO `itembase` (`ITID`,`ITNIVELMAGICO`,`ITDURABILIDADE`,`ITNOME`,`ITDESCRICAO`,`ITALCANCE`,`ITVELOCIDADE`,`ITDROPAVEL`,`ITRACA`,`ITDANOMAX`,`ITDANOMIN`,`ITMODIFICADOR`,`ITVALOR`,`ITDEFESA`,`ITISTEMP`,`ITDURACAO`,`ITTIPO`,`ITLEALARANHA`,`ITLEALESCORPIAO`,`ITLEALLOUVA`,`ITLEALVESPA`,`ITLEALBESOURO`,`ITIDMODELO`,`ITIDTEXTURA`,`ITTIPOUSO`,`ITPRECO`,`ITIDTIPOITEM`,`ITIDHUD`) VALUES 
 (0,0,20,'Buzina',NULL,50,1,0,2,5,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0),
 (1,0,20,'Varinha',NULL,50,2,0,2,4,3,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,1,1),
 (2,0,20,'Soco Mágico',NULL,10,0,0,2,7,3,0,0,0,0,0,1,0,0,0,0,0,2,2,0,0,2,2),
 (3,0,20,'Bazuca',NULL,100,0,0,3,10,1,5,0,0,0,0,1,0,0,0,0,0,3,3,0,0,3,3),
 (4,0,20,'Martelo de Guerra',NULL,0,0,0,3,0,0,0,0,0,0,0,1,0,0,0,0,0,4,4,0,0,4,4),
 (5,0,20,'Metralhadora Quad Giratória',NULL,50,1,0,3,5,0,4,0,0,0,0,1,0,0,0,0,0,5,5,0,0,5,5),
 (6,0,20,'Maça Estrela',NULL,0,0,0,3,5,1,4,0,0,0,0,1,0,0,0,0,0,6,6,0,0,6,6),
 (7,0,20,'Katana',NULL,0,3,0,4,2,1,4,0,0,0,0,1,0,0,0,0,0,7,7,0,0,7,7),
 (8,0,20,'Lançador de Dardos',NULL,50,5,0,4,3,2,2,0,0,0,0,1,0,0,0,0,0,8,8,0,0,8,8),
 (9,0,20,'Machado',NULL,0,1,0,4,3,1,3,0,0,0,0,1,0,0,0,0,0,9,9,0,0,9,9),
 (10,0,20,'Palito de Fósforo',NULL,0,4,0,5,4,3,2,0,0,0,0,1,0,0,0,0,0,10,10,0,0,10,10),
 (11,0,20,'Vassoura',NULL,0,5,0,5,3,2,1,0,0,0,0,1,0,0,0,0,0,11,11,0,0,11,11),
 (12,0,20,'Pu Dao',NULL,0,7,0,5,3,1,4,0,0,0,0,1,0,0,0,0,0,12,12,0,0,12,12),
 (13,0,20,'Espingarda de Rolha',NULL,200,1,0,6,7,3,3,0,0,0,0,1,0,0,0,0,0,13,13,0,0,13,13),
 (14,0,1,'Mamona',NULL,0,0,0,6,20,20,0,0,0,0,0,1,0,0,0,0,0,14,14,0,0,14,14),
 (15,0,20,'Estilingue',NULL,10,3,0,6,5,3,1,0,0,0,0,1,0,0,0,0,0,15,15,0,0,15,15),
 (16,0,5,'Cartola',NULL,0,0,0,2,0,0,0,0,1,0,0,2,0,0,0,0,0,16,16,0,0,16,16),
 (17,0,10,'Tênis',NULL,0,0,0,2,0,0,0,0,2,0,0,2,0,0,0,0,0,17,17,0,0,17,17),
 (18,0,10,'Elmo de Hércules',NULL,0,0,0,3,0,0,0,0,5,0,0,2,0,0,0,0,0,18,18,0,0,18,18),
 (19,0,7,'Elmo Bárbaro',NULL,0,0,0,3,0,0,0,0,3,0,0,2,0,0,0,0,0,19,19,0,0,19,19),
 (20,0,10,'Óculos Escuros',NULL,0,0,0,4,0,0,0,0,2,0,0,2,0,0,0,0,0,20,20,0,0,20,20),
 (21,0,7,'Gorro',NULL,0,0,0,4,0,0,0,0,4,0,0,2,0,0,0,0,0,21,21,0,0,21,21),
 (22,0,5,'Chachi',NULL,0,0,0,5,0,0,0,0,4,0,0,2,0,0,0,0,0,22,22,0,0,22,22),
 (23,0,10,'Chapéu de Palha',NULL,0,0,0,5,0,0,0,0,3,0,0,2,0,0,0,0,0,23,23,0,0,23,23),
 (24,0,10,'Óculos de Aviador',NULL,0,0,0,6,0,0,0,0,2,0,0,2,0,0,0,0,0,24,24,0,0,24,24),
 (25,0,10,'Máscara de Gás',NULL,0,0,0,6,0,0,0,0,3,0,0,2,0,0,0,0,0,25,25,0,0,25,25),
 (26,0,0,'Passaporte',NULL,0,0,0,1,0,0,0,0,0,0,0,5,0,0,0,0,0,26,26,0,0,26,26),
 (27,0,0,'Polpa de Formiga',NULL,0,0,0,1,0,0,0,20,0,0,0,0,0,0,0,0,0,27,27,1,0,27,27),
 (28,0,0,'Polpa de Cupim',NULL,0,0,0,1,0,0,0,5,0,0,0,0,0,0,0,0,0,28,28,2,0,28,28),
 (29,0,0,'Polpa de Barata',NULL,0,0,0,1,0,0,0,40,0,0,0,0,0,0,0,0,0,29,29,1,0,29,29),
 (30,0,0,'Polpa de Tatu',NULL,0,0,0,1,0,0,0,10,0,0,0,0,0,0,0,0,0,30,30,2,0,30,30),
 (31,0,0,'Asa de Libélula',NULL,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,31,31,3,0,31,31),
 (32,0,0,'Perfume de Percevejo',NULL,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,32,32,3,0,32,32),
 (33,0,0,'Mel de Abelha',NULL,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,33,33,3,0,33,33),
 (34,0,0,'Tesoura de Barbeiro',NULL,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,34,34,3,0,34,34),
 (35,0,0,'Rabo de Calango',NULL,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,35,35,3,0,35,35),
 (36,0,0,'Ovo de Lagartixa',NULL,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,36,36,3,0,36,36),
 (37,0,0,'Língua de Sapo',NULL,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,37,37,3,0,37,37),
 (38,0,0,'Língua de Camaleão',NULL,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,38,38,3,0,38,38);
/*!40000 ALTER TABLE `itembase` ENABLE KEYS */;


--
-- Definition of table `jogador`
--

DROP TABLE IF EXISTS `jogador`;
CREATE TABLE `jogador` (
  `JDSENHA` varchar(30) default NULL,
  `JDEMAIL` varchar(30) default NULL,
  `JDNOME` varchar(30) default NULL,
  `JDID` int(11) NOT NULL,
  `JDLOGIN` varchar(30) NOT NULL,
  `JDDATANASC` varchar(30) default NULL,
  PRIMARY KEY  USING BTREE (`JDLOGIN`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `jogador`
--

/*!40000 ALTER TABLE `jogador` DISABLE KEYS */;
INSERT INTO `jogador` (`JDSENHA`,`JDEMAIL`,`JDNOME`,`JDID`,`JDLOGIN`,`JDDATANASC`) VALUES 
 ('1350250','edragon975@gmail.com','Eder',1,'Edin','06/07/89'),
 ('wurzelion','eduardofantini@gmail.com','Eduardo',3,'fantini','10/02/79'),
 ('doido','dotdrums@gmail.com','Paulo',4,'himura','14/09/84'),
 ('140387','tarcisio_resende@yahoo.com.br','Tarcísio',2,'shendoo','03/03/87');
/*!40000 ALTER TABLE `jogador` ENABLE KEYS */;


--
-- Definition of table `jogador_personagem`
--

DROP TABLE IF EXISTS `jogador_personagem`;
CREATE TABLE `jogador_personagem` (
  `PGID` int(11) default NULL,
  `JDID` int(11) default NULL,
  KEY `JDID` (`JDID`),
  KEY `PGID` (`PGID`),
  CONSTRAINT `jogador_personagem_ibfk_2` FOREIGN KEY (`PGID`) REFERENCES `personagem` (`PGID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `jogador_personagem`
--

/*!40000 ALTER TABLE `jogador_personagem` DISABLE KEYS */;
/*!40000 ALTER TABLE `jogador_personagem` ENABLE KEYS */;


--
-- Definition of table `personagem`
--

DROP TABLE IF EXISTS `personagem`;
CREATE TABLE `personagem` (
  `PGID` int(11) NOT NULL,
  `PGNOME` varchar(30) default NULL,
  `PGNIVEL` int(11) default NULL,
  `PGDINHEIRO` int(11) default NULL,
  `PGEXPERIENCIA` int(11) default NULL,
  `PGEXPERIENCIAMAX` int(11) default NULL,
  `PGPONTOSVIDA` int(11) default NULL,
  `PGPONTOSVIDAMAX` int(11) default NULL,
  `PGPONTOSPODER` int(11) default NULL,
  `PGPONTOSPODERMAX` int(11) default NULL,
  `PGDIRECAO` float default NULL,
  `PGVELOCIDADE` float default NULL,
  `PGRACA` int(11) default NULL,
  `PGTEMPORESPAW` int(11) default NULL,
  `PGFORCA` int(11) default NULL,
  `PGAGILIDADE` int(11) default NULL,
  `PGDESTREZA` int(11) default NULL,
  `PGRESISTENCIA` int(11) default NULL,
  `PGINSTINTO` int(11) default NULL,
  `PGATAQUESDISTANCIA` int(11) default NULL,
  `PGATAQUESCORPO` int(11) default NULL,
  `PGDANOCORPO` int(11) default NULL,
  `PGDANODISTANCIA` int(11) default NULL,
  `PGDEFESA` int(11) default NULL,
  `PGTAXAATAQUE` int(11) default NULL,
  `PGTEMPOCARGA` int(11) default NULL,
  `PGTIPOPERSONAGEM` int(11) default NULL,
  `PGLEALARANHA` int(11) default NULL,
  `PGLEALBESOURO` int(11) default NULL,
  `PGLEALESCORPIAO` int(11) default NULL,
  `PGLEALLOUVA` int(11) default NULL,
  `PGLEALVESPA` int(11) default NULL,
  `PGIDARMOR` int(11) default NULL,
  `PGIDWEAPON` int(11) default NULL,
  `PGX` float default NULL,
  `PGZ` float default NULL,
  `PGY` float default NULL,
  `PGIDTEXTURA` int(11) default NULL,
  `PGIDMODELO` int(11) default NULL,
  `PGBONUSPOINTSPRIMARIAS` int(11) default '0',
  `PGBONUSPOINTSPODER` int(11) default '0',
  `PGISBASE` tinyint(1) default '0',
  `PGIDHUD` int(11) default NULL,
  PRIMARY KEY  (`PGID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `personagem`
--

/*!40000 ALTER TABLE `personagem` DISABLE KEYS */;
INSERT INTO `personagem` (`PGID`,`PGNOME`,`PGNIVEL`,`PGDINHEIRO`,`PGEXPERIENCIA`,`PGEXPERIENCIAMAX`,`PGPONTOSVIDA`,`PGPONTOSVIDAMAX`,`PGPONTOSPODER`,`PGPONTOSPODERMAX`,`PGDIRECAO`,`PGVELOCIDADE`,`PGRACA`,`PGTEMPORESPAW`,`PGFORCA`,`PGAGILIDADE`,`PGDESTREZA`,`PGRESISTENCIA`,`PGINSTINTO`,`PGATAQUESDISTANCIA`,`PGATAQUESCORPO`,`PGDANOCORPO`,`PGDANODISTANCIA`,`PGDEFESA`,`PGTAXAATAQUE`,`PGTEMPOCARGA`,`PGTIPOPERSONAGEM`,`PGLEALARANHA`,`PGLEALBESOURO`,`PGLEALESCORPIAO`,`PGLEALLOUVA`,`PGLEALVESPA`,`PGIDARMOR`,`PGIDWEAPON`,`PGX`,`PGZ`,`PGY`,`PGIDTEXTURA`,`PGIDMODELO`,`PGBONUSPOINTSPRIMARIAS`,`PGBONUSPOINTSPODER`,`PGISBASE`,`PGIDHUD`) VALUES 
 (0,NULL,1,0,0,100,10,10,20,20,0,10,2,0,1,3,5,2,4,0,1,1,0,2,13,0,2,100,0,0,0,0,-1,-1,0,0,0,1,1,5,0,1,2),
 (1,NULL,1,0,0,100,30,30,5,5,0,10,3,0,6,1,1,6,1,0,6,6,0,6,11,0,2,0,100,0,0,0,-1,4,0,0,0,7,7,5,0,1,7),
 (2,NULL,1,0,0,100,15,15,30,30,0,10,4,0,2,2,3,3,5,0,2,2,0,3,12,0,2,0,0,100,0,0,-1,-1,0,0,0,13,13,5,0,1,13),
 (3,NULL,1,0,0,100,5,5,20,20,0,10,5,0,3,5,2,1,4,0,3,3,0,5,15,0,2,0,0,0,100,0,-1,-1,0,0,0,19,19,5,0,1,19),
 (4,NULL,1,0,0,100,15,15,5,5,0,10,6,0,1,3,7,3,1,0,1,1,0,3,13,0,2,0,0,0,0,100,-1,-1,0,0,0,25,25,5,0,1,25),
 (5,'Cupim',1,1,0,100,10,10,20,20,0,10,7,0,5,3,2,3,2,0,5,5,0,3,13,0,3,0,0,0,0,0,-1,-1,0,0,0,30,30,0,0,1,30),
 (6,'Formiga',1,1,0,100,10,10,20,20,0,10,8,0,3,2,4,2,4,0,3,3,0,2,12,0,3,0,0,0,0,0,-1,-1,0,0,0,31,31,0,0,1,31),
 (7,'Barbeiro',2,5,0,200,30,30,25,25,0,10,9,0,3,2,3,4,8,0,3,3,0,4,12,0,3,0,0,0,0,0,-1,-1,0,0,0,32,32,0,0,1,32),
 (8,'Barata',3,7,0,300,30,30,25,25,0,10,10,0,5,4,5,6,5,0,5,5,0,6,14,0,3,0,0,0,0,0,-1,-1,0,0,0,33,33,0,0,1,33),
 (9,'Tatu-Bolinha',5,10,0,500,125,125,10,10,0,10,11,0,1,5,1,25,2,0,1,1,0,25,15,0,3,0,0,0,0,0,-1,-1,0,0,0,34,34,0,0,1,34),
 (10,'Libélula',9,10,0,4000,10,10,160,160,0,10,12,0,0,20,2,3,30,0,0,0,0,3,30,0,3,0,0,0,0,0,-1,-1,0,0,0,35,35,0,0,1,35),
 (11,'Percevejo',11,15,0,10000,70,70,70,70,0,10,13,0,13,12,12,14,14,0,13,13,0,14,22,0,3,0,0,0,0,0,-1,-1,0,0,0,36,36,0,0,1,36),
 (12,'Abelha',13,20,0,30000,75,75,75,75,0,10,14,0,15,15,15,15,15,0,15,15,0,15,25,0,3,0,0,0,0,0,-1,-1,0,0,0,37,37,0,0,1,37),
 (13,'Lagartixa',15,40,0,50000,70,70,70,70,0,10,15,0,17,17,17,17,17,0,17,17,0,17,27,0,3,0,0,0,0,0,-1,-1,0,0,0,38,38,0,0,1,38),
 (14,'Calango',19,80,0,400000,10,10,10,10,0,10,16,0,80,10,5,5,5,0,80,80,0,5,20,0,3,0,0,0,0,0,-1,-1,0,0,0,39,39,0,0,1,39),
 (15,'Sapo',20,160,0,500000,150,150,160,160,0,10,17,0,40,10,10,30,20,0,40,40,0,35,20,0,3,0,0,0,0,0,-1,-1,0,0,0,40,40,0,0,1,40),
 (16,'Joaninha',21,200,0,600000,150,150,250,250,0,10,18,0,10,10,10,35,50,0,10,10,0,35,20,0,3,0,0,0,0,0,-1,-1,0,0,0,41,41,0,0,1,41),
 (17,'Camaleão',25,400,0,1000000,160,160,160,160,0,10,19,0,30,20,15,40,30,0,30,30,0,50,30,0,3,0,0,0,0,0,-1,-1,0,0,0,42,42,0,0,1,42),
 (18,'TanDan',30,1000,0,0,250,250,50,50,0,10,8,0,70,30,10,50,10,0,70,70,0,10,20,0,4,0,0,0,0,0,-1,-1,0,0,0,43,43,0,0,0,43);
/*!40000 ALTER TABLE `personagem` ENABLE KEYS */;


--
-- Definition of table `personagem_cenario`
--

DROP TABLE IF EXISTS `personagem_cenario`;
CREATE TABLE `personagem_cenario` (
  `CNID` int(11) default NULL,
  `PGID` int(11) default NULL,
  KEY `CNID` (`CNID`),
  KEY `PGID` (`PGID`),
  CONSTRAINT `FK_personagem_cenario_1` FOREIGN KEY (`CNID`) REFERENCES `cenario` (`CNID`),
  CONSTRAINT `FK_personagem_cenario_2` FOREIGN KEY (`PGID`) REFERENCES `personagem` (`PGID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `personagem_cenario`
--

/*!40000 ALTER TABLE `personagem_cenario` DISABLE KEYS */;
INSERT INTO `personagem_cenario` (`CNID`,`PGID`) VALUES 
 (1,6),
 (1,6),
 (1,6),
 (1,6),
 (1,6),
 (1,6),
 (1,6),
 (1,6),
 (1,6),
 (1,6);
/*!40000 ALTER TABLE `personagem_cenario` ENABLE KEYS */;


--
-- Definition of table `poder`
--

DROP TABLE IF EXISTS `poder`;
CREATE TABLE `poder` (
  `PDID` int(11) NOT NULL,
  `PDNIVEL` int(11) default NULL,
  `PDDESCRICAO` varchar(200) default NULL,
  `PDCUSTOPP` int(11) default NULL,
  `PDCUSTOTC` int(11) default NULL,
  `PDDANO` int(11) default NULL,
  `PDTIPOBUFF` int(11) default NULL,
  PRIMARY KEY  (`PDID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `poder`
--

/*!40000 ALTER TABLE `poder` DISABLE KEYS */;
/*!40000 ALTER TABLE `poder` ENABLE KEYS */;


--
-- Definition of table `poder_personagem`
--

DROP TABLE IF EXISTS `poder_personagem`;
CREATE TABLE `poder_personagem` (
  `PGID` int(11) default NULL,
  `PDID` int(11) default NULL,
  KEY `PGID` (`PGID`),
  KEY `PDID` (`PDID`),
  CONSTRAINT `poder_personagem_ibfk_1` FOREIGN KEY (`PGID`) REFERENCES `personagem` (`PGID`),
  CONSTRAINT `poder_personagem_ibfk_2` FOREIGN KEY (`PDID`) REFERENCES `poder` (`PDID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `poder_personagem`
--

/*!40000 ALTER TABLE `poder_personagem` DISABLE KEYS */;
/*!40000 ALTER TABLE `poder_personagem` ENABLE KEYS */;


--
-- Definition of table `portal`
--

DROP TABLE IF EXISTS `portal`;
CREATE TABLE `portal` (
  `PTID` int(11) NOT NULL,
  `PTLOCZ` float default NULL,
  `PTLOCX` float default NULL,
  `PTLOCY` float default NULL,
  `PTDESTZ` float default NULL,
  `PTDESTX` float default NULL,
  `PTDESTY` float default NULL,
  `PTIDCENARIODEST` int(11) default NULL,
  `PTDIRECAO` int(11) default NULL,
  PRIMARY KEY  (`PTID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `portal`
--

/*!40000 ALTER TABLE `portal` DISABLE KEYS */;
/*!40000 ALTER TABLE `portal` ENABLE KEYS */;


--
-- Definition of table `portal_cenario`
--

DROP TABLE IF EXISTS `portal_cenario`;
CREATE TABLE `portal_cenario` (
  `PTID` int(11) default NULL,
  `CNID` int(11) default NULL,
  KEY `PTID` (`PTID`),
  KEY `CNID` (`CNID`),
  CONSTRAINT `portal_cenario_ibfk_1` FOREIGN KEY (`PTID`) REFERENCES `portal` (`PTID`),
  CONSTRAINT `portal_cenario_ibfk_2` FOREIGN KEY (`CNID`) REFERENCES `cenario` (`CNID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `portal_cenario`
--

/*!40000 ALTER TABLE `portal_cenario` DISABLE KEYS */;
/*!40000 ALTER TABLE `portal_cenario` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
