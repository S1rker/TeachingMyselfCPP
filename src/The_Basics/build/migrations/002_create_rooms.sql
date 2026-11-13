CREATE TABLE rooms (
    id   INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE COLLATE NOCASE
);

CREATE TABLE user_rooms (
    user_id    INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    room_id    INTEGER NOT NULL REFERENCES rooms(id) ON DELETE CASCADE,
    granted_at TEXT    NOT NULL DEFAULT (datetime('now')),
    PRIMARY KEY (user_id, room_id)
);

CREATE INDEX idx_user_rooms_room ON user_rooms(room_id);