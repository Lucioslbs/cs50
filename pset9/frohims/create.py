import sqlite3

# Conecte-se ao banco de dados (ou crie um novo)
conn = sqlite3.connect('froshims.db')

# Crie um cursor para interagir com o banco de dados
cursor = conn.cursor()

# Crie a tabela registrants
cursor.execute('''
CREATE TABLE IF NOT EXISTS registrants (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    sport TEXT NOT NULL
);
''')

# Salve as mudanças e feche a conexão
conn.commit()
conn.close()
