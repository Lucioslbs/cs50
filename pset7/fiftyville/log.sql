-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Listar todas as tabelas
.tables

-- Inspecionar a estrutura da tabela crime_scene_reports
.schema crime_scene_reports

-- Inspecionar a estrutura da tabela suspects
.schema suspects

-- Inspecionar a estrutura da tabela flights
.schema flights

-- Inspecionar a estrutura da tabela people
.schema people

-- Inspecionar a estrutura da tabela vehicles
.schema vehicles

-- Buscar relatórios da cena do crime
SELECT *
FROM crime_scene_reports
WHERE date = '2020-07-28' AND location = 'Chamberlin Street';

-- Buscar suspeitos associados ao local do crime
SELECT s.name, s.address, s.ssn
FROM suspects s
JOIN crime_scene_reports c ON s.address = c.location
WHERE c.date = '2020-07-28' AND c.location = 'Chamberlin Street';

-- Buscar voos que partiram na data do crime
SELECT *
FROM flights
WHERE departure_date = '2020-07-28' AND departure_city = 'Fiftyville';

-- Associar pessoas aos voos
SELECT p.name, f.destination_city, f.flight_number
FROM people p
JOIN flights f ON p.flight_id = f.id
WHERE f.departure_date = '2020-07-28' AND f.departure_city = 'Fiftyville';

-- Buscar veículos roubados na data do crime
SELECT p.name, v.owner, v.license_plate
FROM people p
JOIN vehicles v ON p.ssn = v.owner_ssn
WHERE v.date_reported_stolen = '2020-07-28';

