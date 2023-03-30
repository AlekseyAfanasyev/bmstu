import telebot
from telebot import types
import pytz
from datetime import datetime


token = ''
with open('token.txt', 'r') as f:
    token=f.readline()
bot = telebot.TeleBot(token)

newYorkTz = pytz.timezone("America/New_York") 
timeInNewYork = datetime.now(newYorkTz)
currentTimeInNewYork = timeInNewYork.strftime("%H:%M:%S")

moscowTz = pytz.timezone("Europe/Moscow") 
timeInMoscow = datetime.now(moscowTz)
currentTimeInMoscow = timeInMoscow.strftime("%H:%M:%S")

tokyoTz = pytz.timezone("Asia/Tokyo") 
timeInTokyo = datetime.now(tokyoTz)
currentTimeInTokyo = timeInTokyo.strftime("%H:%M:%S")


@bot.message_handler(commands=["start"])
def start(m, res=False):
    markup=types.ReplyKeyboardMarkup(resize_keyboard=True)
    item1=types.KeyboardButton("Нью-Йорк")
    item2=types.KeyboardButton("Москва")
    item3=types.KeyboardButton("Токио")
    markup.add(item1)
    markup.add(item2)
    markup.add(item3)
    bot.send_message(m.chat.id, 'Выберите город:', reply_markup=markup)

@bot.message_handler(content_types=["text"])
def handle_text(message):
    if message.text.strip() == 'Нью-Йорк':
        bot.send_message(message.chat.id, 'Время в Нью-Йорке: ' + currentTimeInNewYork)
    elif message.text.strip() == 'Москва':
        bot.send_message(message.chat.id, 'Время в Москве: ' + currentTimeInMoscow)
    elif message.text.strip() == 'Токио':
        bot.send_message(message.chat.id, 'Время в Токио: ' + currentTimeInTokyo)
    else:
        bot.send_message(message.chat.id, 'Неизвестная команда')

bot.polling(none_stop=True, interval=0)