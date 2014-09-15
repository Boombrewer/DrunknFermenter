-- phpMyAdmin SQL Dump
-- version 4.0.4
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jan 07, 2014 at 03:13 PM
-- Server version: 5.6.12-log
-- PHP Version: 5.4.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `drunknfermenter`
--
CREATE DATABASE IF NOT EXISTS `drunknfermenter` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `drunknfermenter`;

-- --------------------------------------------------------

--
-- Table structure for table `carboy1`
--

CREATE TABLE IF NOT EXISTS `carboy1` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` text NOT NULL,
	`datetime` DATETIME() NULL,
	`insideTemp` decimal(4,2) NOT NULL,
	`car1Temp` decimal(4,2) NOT NULL,
	`setTempCar1` int(3) NOT NULL,
	`fanStatus` tinyint(1) NOT NULL DEFAULT 0,
	`freezerStatus` tinyint(1) NOT NULL DEFAULT 0,
	`heater1Status` tinyint(1) NOT NULL DEFAULT 0,

PRIMARY KEY (`id`)
) ENGINE=InnoDB	DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `carboy2`
--

CREATE TABLE IF NOT EXISTS `carboy2` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` text NOT NULL,
	`datetime` DATETIME() NULL,
	`insideTemp` decimal(4,2) NOT NULL,
	`car2Temp` decimal(4,2) NOT NULL,
	`setTempCar2` int(3) NOT NULL,
	`fanStatus` tinyint(1) NOT NULL DEFAULT 0,
	`freezerStatus` tinyint(1) NOT NULL DEFAULT 0,
	`heater2Status` tinyint(1) NOT NULL DEFAULT 0,

PRIMARY KEY (`id`)
) ENGINE=InnoDB	DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `carboy3`
--

CREATE TABLE IF NOT EXISTS `carboy3` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` text NOT NULL,
	`datetime` DATETIME() NULL,
	`insideTemp` decimal(4,2) NOT NULL,
	`car3Temp` decimal(4,2) NOT NULL,
	`recircStatus` tinyint(1) NOT NULL DEFAULT 0,
	`freezerStatus` tinyint(1) NOT NULL DEFAULT 0,

PRIMARY KEY (`id`)
) ENGINE=InnoDB	DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `config`
--

CREATE TABLE `config` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`configName` varchar(50) NOT NULL,
	`configValue` longtext NOT NULL,
	`displayName` varchar(65) NOT NULL,
	`showOnPanel` tinyint(2) NOT NULL,
	`createdDate` DATETIME() NULL,
	`modifiedDate` DATETIME() NULL,

	PRIMARY KEY (`id`),
	UNIQUE KEY `configName_UNIQUE` (`configName`)
) ENGINE=InnoDB	DEFAULT CHARSET=latin1;

--
-- Dumping data for table `config`
--

INSERT INTO `config` ( configName, configValue, displayName, showOnPanel, createdDate, modifiedDate ) VALUES
( 'showCar1Info', '1', 'Carboy 1 Stats', '1', NOW(), NOW() ),
( 'showCar2Info', '1', 'Carboy 2 Stats', '1', NOW(), NOW() ),
( 'showCar3Info', '1', 'Carboy 3 Stats', '1', NOW(), NOW() ),
( 'logoUrl', 'img/logo.png', 'Logo Url', '0', NOW(), NOW() ),
( 'adminLogoUrl', 'admin/img/logo.png', 'Admin Logo Url', '0', NOW(), NOW() ),
( 'headerText', 'Currently Fermenting', 'Header Text', '0', NOW(), NOW() ),
( 'numberOfCars', '0', 'Number of Carboys', '0', NOW(), NOW() ),
( 'version', '1.0.0.279', 'Version', '0', NOW(), NOW() ),
( 'headerTextTruncLen' ,'25', 'Header Text Truncate Length', '0', NOW(), NOW() );


-- --------------------------------------------------------

--
-- Table structure for table `fermTempProfiles`
--

CREATE TABLE IF NOT EXISTS `fermTempProfiles` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`profileName` text NOT NULL,
	`startTemp` int(3) NOT NULL,
	`numOfTrans` int(2) NOT NULL,
	`dayTransStart` int(3) NOT NULL,
	`dayTransStop` int(3) NOT NULL,
	`endTemp` int(3) NOT NULL,
	`createdDate` DATETIME() NULL,
	`modifiedDate` DATETIME() NULL,
	
	PRIMARY KEY (`id`)
) ENGINE=InnoDB	DEFAULT CHARSET=latin1;

--
-- Dumping data for table `fermTempProfiles`
--

INSERT INTO `fermTempProfiles` ( profileName, startTemp, numOfTrans, dayTransStart, dayTransStop, endTemp,
createdDate, modifiedDate ) VALUES
( 'Cold Crash', currentTemp, 1, 0, 2, 40, NOW(), NOW() ),
( 'Heat Ramp', currentTemp, 1, 0, 3, 72, NOW(), NOW() );

-- --------------------------------------------------------

--
-- Table structure for table `Users`
--

CREATE TABLE `users` (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`username` varchar(65) CHARACTER SET utf8 NOT NULL,
	`password` varchar(65) CHARACTER SET utf8 NOT NULL,
	`name` varchar(65) CHARACTER SET utf8 NOT NULL,
	`email` varchar(65) CHARACTER SET utf8 NOT NULL,
	`createdDate` TIMESTAMP NULL,
	`modifiedDate` TIMESTAMP NULL,

	PRIMARY KEY (`id`),
	UNIQUE KEY `username_UNIQUE` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


-- ---------------------------------------------------------
--
-- Create View `vwGetActiveTaps`
--

/* CREATE VIEW vwGetActiveTaps
AS

SELECT
	t.id,
	b.name,
	bs.name as 'style',
	b.notes,
	t.ogAct,
	t.fgAct,
	t.srmAct,
	t.ibuAct,
	t.startAmount,
	IFNULL(p.amountPoured, 0) as amountPoured,
	t.startAmount - IFNULL(p.amountPoured, 0) as remainAmount,
	t.tapNumber,
	s.rgb as srmRgb
FROM taps t
	LEFT JOIN beers b ON b.id = t.beerId
	LEFT JOIN beerStyles bs ON bs.id = b.beerStyleId
	LEFT JOIN srmRgb s ON s.srm = t.srmAct
	LEFT JOIN vwGetTapsAmountPoured as p ON p.tapId = t.Id
WHERE t.active = true
ORDER BY t.tapNumber;
*/

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
