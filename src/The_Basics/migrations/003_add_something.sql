INSERT INTO rooms (name) VALUES ('A'), ('B'), ('C'), ('D');

INSERT INTO user_rooms (user_id, room_id)
SELECT u.id, r.id FROM users u, rooms r
WHERE (u.username = 'something'  AND r.name IN ('A','B'))
   OR (u.username = 'bigthing'  AND r.name IN ('C','D'))
   OR (u.username = 'testcode' AND r.name IN ('A','C'));