import asyncio
from telegram import Update
from telegram.ext import Application, CommandHandler, MessageHandler, filters
import httpx

TELEGRAM_TOKEN = "seu_token_aqui"
API_URL = "http://localhost:8000/execute"

async def start(update: Update, context):
    await update.message.reply_text("🎮 Dead Wasteland Controller\nEnvie comandos para controlar o jogo!")

async def handle_message(update: Update, context):
    """Recebe mensagem do usuário e envia para a API"""
    user_command = update.message.text
    
    # Envia para a API
    async with httpx.AsyncClient() as client:
        response = await client.post(API_URL, json={"command": user_command, "use_grok": False})
        
        if response.status_code == 200:
            result = response.json()
            await update.message.reply_text(f"✅ Executado: {result['action']}")
        else:
            await update.message.reply_text("❌ Erro ao executar comando")

def main():
    app = Application.builder().token(TELEGRAM_TOKEN).build()
    
    app.add_handler(CommandHandler("start", start))
    app.add_handler(MessageHandler(filters.TEXT & ~filters.COMMAND, handle_message))
    
    app.run_polling()

if __name__ == "__main__":
    main()
