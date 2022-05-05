-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Reading the description of crime scene - Theft of CS50 duck.
SELECT description, street
  FROM crime_scene_reports
 WHERE (year = 2021)
   AND (month = 7)
   AND (day = 28);

-- Reading transcripts of interviews of witnesses related to the theft.
SELECT name, transcript
  FROM interviews
 WHERE (year = 2021)
   AND (month = 7)
   AND (day = 28);

-- Receiving lincence plates from bakery parking lot from that time frame (minute = 15 -> 25) of exiting cars.
SELECT license_plate, hour, minute
  FROM bakery_security_logs
 WHERE (year = 2021)
   AND (month = 7)
   AND (day = 28)
   AND (hour = 10)
   AND (minute BETWEEN 15 AND 25)
   AND (activity = "exit");

-- Overview of atm transaction that day on location Leggett Street, type withdraw.
SELECT account_number, amount
  FROM atm_transactions
 WHERE (year = 2021)
   AND (month = 7)
   AND (day = 28)
   AND (atm_location = "Leggett Street")
   AND (transaction_type = "withdraw");

-- Overview of calls that day with duration < 60 seconds.
SELECT caller, receiver, duration
  FROM phone_calls
 WHERE (year = 2021)
   AND (month = 7)
   AND (day = 28)
   AND (duration < 60);

-- Find the first flight on 29th of July 2021 departing from Fiftyville Regional Airport (destination and id).
  SELECT flights.origin_airport_id, flights.destination_airport_id, flights.id
    FROM flights
    JOIN airports
      ON flights.origin_airport_id = airports.id
   WHERE airports.city = "Fiftyville"
     AND (flights.year = 2021)
     AND (flights.month = 7)
     AND (flights.day = 29)
ORDER BY flights.hour, flights.minute LIMIT 1;

-- Get name of the destination city of the flight (--> New York).
SELECT city
  FROM airports
 WHERE id = (
     SELECT flights.destination_airport_id
       FROM flights
       JOIN airports
         ON flights.origin_airport_id = airports.id
      WHERE airports.city = "Fiftyville"
        AND (flights.year = 2021)
        AND (flights.month = 7)
        AND (flights.day = 29)
   ORDER BY flights.hour, flights.minute
      LIMIT 1);

-- Find name of thief (--> Bruce).
SELECT people.name
  FROM people
 WHERE people.passport_number = (
     SELECT passengers.passport_number
       FROM passengers
      WHERE passengers.passport_number
         IN (
             SELECT people.passport_number
               FROM people
              WHERE people.license_plate
                 IN (
                     SELECT license_plate
                       FROM bakery_security_logs
                      WHERE (year = 2021)
                        AND (month = 7)
                        AND (day = 28)
                        AND (hour = 10)
                        AND (minute BETWEEN 15 AND 25)
                        AND (activity = "exit"))
                AND people.phone_number
                 IN (
                     SELECT caller
                       FROM phone_calls
                      WHERE (year = 2021)
                        AND (month = 7)
                        AND (day = 28)
                        AND (duration < 60))
                AND people.id
                 IN (
                     SELECT person_id
                       FROM bank_accounts
                      WHERE account_number
                         IN (
                             SELECT account_number
                               FROM atm_transactions
                              WHERE (year = 2021)
                                AND (month = 7)
                                AND (day = 28)
                                AND (atm_location = "Leggett Street")
                                AND (transaction_type = "withdraw"))))
        AND passengers.flight_id = (
            SELECT flights.id
              FROM flights
              JOIN airports
                ON flights.origin_airport_id = airports.id
             WHERE airports.city = "Fiftyville"
               AND (flights.year = 2021)
               AND (flights.month = 7)
               AND (flights.day = 29)
          ORDER BY flights.hour, flights.minute
             LIMIT 1));

-- Find accomplice (--> Robin).
SELECT people.name
 FROM people
WHERE people.phone_number = (
    SELECT phone_calls.receiver
      FROM phone_calls
     WHERE phone_calls.caller = (
         SELECT people.phone_number
           FROM people
          WHERE people.name = "Bruce")
       AND (year = 2021)
       AND (month = 7)
       AND (day = 28)
       AND (duration < 60));