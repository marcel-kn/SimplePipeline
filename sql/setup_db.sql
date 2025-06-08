-- This file sets up the Database for SimplePipeline
-- Creates some sample Data as well

CREATE DATABASE IF NOT EXISTS `simplePipeline`;

USE `simplePipeline`;

--
-- Table structure for table `artists`
--

DROP TABLE IF EXISTS `artists`;
CREATE TABLE `artists` (
  `short_name` varchar(50) NOT NULL,
  `first_name` varchar(30) DEFAULT NULL,
  `last_name` varchar(30) DEFAULT NULL,
  `email` varchar(30) DEFAULT NULL,
  `level` tinyint(4) DEFAULT '0',
  PRIMARY KEY (`short_name`)
);

INSERT INTO artists (short_name, first_name, last_name) 
VALUES ('fsc', 'Franz', 'Schmidt');
INSERT INTO artists (short_name, first_name, last_name) 
VALUES ('hmu', 'Hans', 'Müller');
INSERT INTO artists (short_name, first_name, last_name) 
VALUES ('ttu', 'Tomte', 'Tummetott');

DROP TABLE IF EXISTS `projects`;
CREATE TABLE `projects` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) DEFAULT NULL,
  `path` varchar(200) DEFAULT NULL,
  `description` varchar(500) DEFAULT NULL,
  `status` bit(1) DEFAULT b'1',
  `frameRate` tinyint(4) DEFAULT NULL,
  `resolutionW` smallint(6) DEFAULT NULL,
  `resolutionH` smallint(6) DEFAULT NULL,
  PRIMARY KEY (`id`)
);

INSERT INTO projects (name, path, description, status, frameRate, resolutionW, resolutionH)
VALUES ('The Mushroom Pickers Code of Conduct',
        '/projects/mushroom/',
        'A TV documentary about mushroom hunting.',
        b'1', '25', '1920', '1080');
INSERT INTO projects (name, path, description, status, frameRate, resolutionW, resolutionH)
VALUES ('Chemotoxyl Treatment',
        '/projects/chemotoxyl/',
        'An interactive manual for medical treatment.',
        b'1', '25', '1920', '1080');
INSERT INTO projects (name, path, description, status, frameRate, resolutionW, resolutionH)
VALUES ('Murder City Nights Season 2',
        '/projects/mcn2/',
        'Vfx for Season 2 of the famous detective show.',
        b'1', '25', '1920', '1080');

--
-- Table structure for table `shots`
--

DROP TABLE IF EXISTS `shots`;
CREATE TABLE `shots` (
  `id` int(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `length` int(4) DEFAULT NULL,
  `parent_id` int(11) DEFAULT NULL,
  `description` varchar(500) DEFAULT NULL,
  `thumb_file` varchar(200) DEFAULT NULL,
  `status` varchar(20) DEFAULT NULL,
  `creation_date` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `show_id` int(11) DEFAULT NULL,
  `writeProtected` bit(1) DEFAULT b'0',
  PRIMARY KEY (`id`)
);

INSERT INTO `shots` (name, length, parent_id, description,
                     thumb_file, status, creation_date, show_id, writeProtected)
VALUES ('Shot_000',245,0,'Establisher Shot, Kamerafahrt an großem Fliegenpilz vorbei.',
        '000.jpg','in progress',NULL,0, b'0');
INSERT INTO `shots` (name, length, parent_id, description,
                     thumb_file, status, creation_date, show_id, writeProtected)
VALUES ('Shot_010',80,0,'Rennende Wildschweine im Herbstwald.',
        '000.jpg','in progress',NULL,0, b'0');

--
-- Table structure for table `shows`
--

DROP TABLE IF EXISTS `shows`;
CREATE TABLE `shows` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `parent_id` int(11) DEFAULT NULL,
  `name` varchar(70) DEFAULT NULL,
  `description` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`id`)
);

INSERT INTO shows (parent_id, name, description)
VALUES (0, 'Teil_A', 'Hier wird das Szenario eingeführt.');
INSERT INTO shows (parent_id, name, description)
VALUES (0, 'Teil_B', 'Hier wird das Prinzip erklärt.');
