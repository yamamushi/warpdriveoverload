CREATE DATABASE wdOLoad;
CREATE USER `warp`@`localhost` IDENTIFIED BY 'overload';
GRANT ALL ON `wdOLoad`.* TO `warp`@`localhost`;
CREATE TABLE `wdOLoad`.`wd_gal_class` ( `gclass_id` INT NOT NULL AUTO_INCREMENT UNIQUE PRIMARY KEY, `gclass_name` VARCHAR(16) NOT NULL UNIQUE, `gclass_maxsize` INT NOT NULL ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_galaxies` ( `gal_id` INT NOT NULL AUTO_INCREMENT UNIQUE PRIMARY KEY, `gal_name` VARCHAR(16) NOT NULL UNIQUE, `gal_coords` VARCHAR(16) NOT NULL DEFAULT `0,0,0`, `gal_class` VARCHAR(16) NOT NULL, `gal_size` INT NOT NULL, FOREIGN KEY (`gal_class`) REFERENCES wd_gal_class( `gclass_name` ) ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_secblocks` ( `sblock_id` INT UNIQUE NOT NULL AUTO_INCREMENT PRIMARY KEY, `sblock_name` VARCHAR(16) NOT NULL UNIQUE, `num_sectors` INT NOT NULL DEFAULT `8`, `in_gal` VARCHAR(16) NOT NULL, `gal_coords` VARCHAR(16) NOT NULL DEFAULT `0,0,0`, FOREIGN KEY (`in_gal`) REFERENCES wd_galaxies(`gal_name`) ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_sectors` (`sec_id` INT UNIQUE NOT NULL AUTO_INCREMENT PRIMARY KEY, `sector_name` VARCHAR(16) NOT NULL UNIQUE, `sec_block` VARCHAR(16) NOT NULL, `num_systems` INT NOT NULL, `sblock_coords` VARCHAR(16) NOT NULL DEFAULT `0,0,0`, FOREIGN KEY (`sec_block`) REFERENCES wd_secblocks(`sblock_name`) ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_planet_class` ( `pclass_id` INT NOT NULL UNIQUE AUTO_INCREMENT PRIMARY KEY, `planet_class` VARCHAR(16) NOT NULL UNIQUE ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_climates` ( `climate_id` INT NOT NULL UNIQUE AUTO_INCREMENT PRIMARY KEY, `climate_name` VARCHAR(16) UNIQUE NOT NULL ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_star_class` ( `star_class_ID` VARCHAR(3) UNIQUE NOT NULL PRIMARY KEY, `min_mass` INT NOT NULL, `max_mass` INT NOT NULL, `min_lum` INT NOT NULL, `max_lum` INT NOT NULL, `min_radius` INT NOT NULL, `max_radius` INT NOT NULL, `class_color` VARCHAR(16) NOT NULL, `min_temp` INT NOT NULL, `max_temp` INT NOT NULL ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_systems` (`starsystem_id` INT NOT NULL UNIQUE AUTO_INCREMENT, `starsystem_name` VARCHAR(16) NOT NULL UNIQUE, `num_stars` INT NOT NULL, `sector` VARCHAR(16) NOT NULL, `scoord_x` INT NOT NULL DEFAULT `0`, `scoord_y` INT NOT NULL DEFAULT `0`, `scoord_z` INT NOT NULL DEFAULT `0`, `system_radius` INT NOT NULL, `num_planets` INT NOT NULL DEFAULT `0`, `hab_zone_inner` INT NOT NULL, `hab_zone_outer` INT NOT NULL, FOREIGN KEY (`sector`) REFERENCES wd_sectors(`sector_name`) ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_stars` ( `star_id` VARCHAR(16) UNIQUE PRIMARY KEY NOT NULL, `star_name` VARCHAR(30) NOT NULL UNIQUE, `sys_x_coord` INT NOT NULL DEFAULT `0`, `sys_y_coord` INT NOT NULL DEFAULT `0`, `sys_z_coord` INT NOT NULL DEFAULT `0`, `star_class` VARCHAR(3) NOT NULL, `eff_temp` INT NOT NULL, `color` VARCHAR(16) NOT NULL, `mass` INT NOT NULL, `radius` INT NOT NULL, `luminosity` INT NOT NULL, `grav_radius` INT NOT NULL, `wd_system` VARCHAR(16) NOT NULL, FOREIGN KEY (`wd_system`) REFERENCES wd_systems(`starsystem_name`), FOREIGN KEY (`star_class`) REFERENCES wd_star_class( `star_class_id`) ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_planets` ( `planet_id` INT NOT NULL UNIQUE AUT_INCREMENT PRIMARY KEY, `planet_name` VARCHAR(32) NOT NULL UNIQUE, `system` VARCHAR(16) NOT NULL, `orbital_period` INT NOT NULL, `rotational_period` INT NOT NULL, `is_moon` BOOLEAN NOT NULL DEFAULT `false`, `mass` INT NOT NULL, `radius` INT NOT NULL, `planet_class` VARCHAR(16) NOT NULL, `planet_climate` VARCHAR(16) NOT NULL, `mineral_class` VARCHAR(8) NOT NULL, FOREIGN KEY (`system`) REFERENCES wd_systems(`starsystem_name`), FOREIGN KEY (`planet_class`) REFERENCES wd_planet_classes(`planet_class`), FOREIGN KEY (`planet_climate`) REFERENCES wd_climates(`climate_name`), FOREIGN KEY (`mineral_class`) REFERENCES wd_mineral_templates(`template_name`) ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_factions` ( `fac_id` INT NOT NULL AUTO_INCREMENT UNIQUE PRIMARY KEY, `fac_name` VARCHAR(16) NOT NULL UNIQUE, `fac_hq` VARCHAR(50) NOT NULL, `fac_size` INT NOT NULL DEFAULT `0`, FOREIGN KEY (`fac_hq`) REFERENCES `wd_systems`(`system_name`) ) engine=InnoDB;
CREATE TABLE `wdOLoad`.`wd_users` ( user_id INT NOT NULL AUTO_INCREMENT UNIQUE PRIMARY KEY, username VARCHAR(30) UNIQUE NOT NULL, user_pass VARCHAR(30) NOT NULL, player_fac VARCHAR(16) NOT_NULL DEFAULT `ISSA`, player_prof VARCHAR(16) NOT NULL DEFAULT `cadet`, FOREIGN KEY (`player_fac`) REFERENCES wd_factions(`fac_name`), FOREIGN KEY (`player_prof`) REFERENCES wd_professions(`prof_name`) ) engine=InnoDB;
INSERT INTO `wdOLoad`.`wd_star_class` VALUES ( "O", "16", "999", "30000", "100000", "6.6", "99", "blue", "30000", "100000" );
INSERT INTO `wdOLoad`.`wd_star_class` VALUES ( "B", "2.1", "15.99", "25", "29999", "1.8", "6.5", "blue white", "10000", "29999" );
INSERT INTO `wdOLoad`.`wd_star_class` VALUES ( "A", "1.4", "2.09", "5", "24.9", "1.4", "1.79", "white", "7500", "9999" );
INSERT INTO `wdOLoad`.`wd_star_class` VALUES ( "F", "1.04", "1.39", "1.5", "4.9", "1.15", "1.39", "yellow white", "6000", "7499" );
