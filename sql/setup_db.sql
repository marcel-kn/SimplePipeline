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