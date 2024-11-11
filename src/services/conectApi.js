const Groq = require("groq-sdk");

const groq = new Groq({ apiKey: process.env.API_KEY, dangerouslyAllowBrowser: true });

function createPrompt(selectedValues){
    const json = require(`./prompt.json`);
    const promptJson = json.prompt;
    let prompt = "";

    for (let i = 0,  j = 1; i < promptJson.length; i++, j++) {
        prompt += `${promptJson[i]} ${selectedValues[j] || ''} `;
    }

    return prompt.trim();
}

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
    createPrompt
};