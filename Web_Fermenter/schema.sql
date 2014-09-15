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
-- Table structure for table `set_temp`
--

CREATE TABLE IF NOT EXISTS 'set_temp' (
	'DATETIME' DATETIME() NOT NULL,
	'SET_TEMP_1' float(3,1) NOT NULL,
	'SET_TEMP_2' float(3,1) NOT NULL,

PRIMARY KEY (`DATETIME`)
) ENGINE=InnoDB	DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `current_temp`
--

CREATE TABLE IF NOT EXISTS 'current_temp' (
	'DATETIME' DATETIME() NOT NULL,
	'IN_TEMP' float(3,1) NOT NULL,
	'CAR_1_TEMP' float(3,1) NOT NULL,
	'CAR_2_TEMP' float(3,1) NOT NULL,
	'CAR_3_TEMP' float(3,1) NOT NULL,

PRIMARY KEY (`DATETIME`)
) ENGINE=InnoDB	DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `carboy3`
--

CREATE TABLE IF NOT EXISTS 'status' (
	'DATETIME' DATETIME() NOT NULL,
	'COOL_STATUS' tinyint(1) NOT NULL DEFAULT 0,
	'HEAT_1_STATUS' tinyint(1) NOT NULL DEFAULT 0,
	'HEAT_2_STATUS' tinyint(1) NOT NULL DEFAULT 0,
	'IN_FAN_STATUS' tinyint(1) NOT NULL DEFAULT 0,
	'CAR_3_FAN' tinyint(1) NOT NULL DEFAULT 0,
	'RADIO_1' tinyint(1) NOT NULL DEFAULT 0,
	'RADIO_2' tinyint(1) NOT NULL DEFAULT 0,
	'RADIO_3' tinyint(1) NOT NULL DEFAULT 0,

PRIMARY KEY (`DATETIME`)
) ENGINE=InnoDB	DEFAULT CHARSET=latin1;


