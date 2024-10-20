const Groq = require("groq-sdk");

const groq = new Groq({ apiKey: "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", dangerouslyAllowBrowser: true });

async function sendPrompt(prompt) {
    const chatCompletion = await getGroqChatCompletion(prompt);
    return chatCompletion.choices[0]?.message?.content || "";
}

async function getGroqChatCompletion(prompt) {
    return groq.chat.completions.create({
        messages: [
            {
                role: "user",
                content: prompt,
            },
        ],
        model: "llama-3.1-8b-instant",
    });
}

module.exports = {
    sendPrompt,
};