-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.0.67-community-nt


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
  PRIMARY KEY  (`ITID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `itembase`
--

/*!40000 ALTER TABLE `itembase` DISABLE KEYS */;
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
  `JDLOGIN` varchar(30) default NULL,
  `JDDATANASC` varchar(30) default NULL,
  PRIMARY KEY  (`JDID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `jogador`
--

/*!40000 ALTER TABLE `jogador` DISABLE KEYS */;
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
  CONSTRAINT `jogador_personagem_ibfk_1` FOREIGN KEY (`JDID`) REFERENCES `jogador` (`JDID`),
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
  PRIMARY KEY  (`PGID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `personagem`
--

/*!40000 ALTER TABLE `personagem` DISABLE KEYS */;
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
  CONSTRAINT `personagem_cenario_ibfk_1` FOREIGN KEY (`CNID`) REFERENCES `cenario` (`CNID`),
  CONSTRAINT `personagem_cenario_ibfk_2` FOREIGN KEY (`PGID`) REFERENCES `personagem` (`PGID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `personagem_cenario`
--

/*!40000 ALTER TABLE `personagem_cenario` DISABLE KEYS */;
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
