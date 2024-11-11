import {createPrompt, sendPrompt} from "../services/conectApi";

export default async function Login(req, res) {
    if (req.method === 'POST') {
        const { username, password, estado_animo, edad, genero_literatura } = req.body;

        if (!username || !password || !edad || !estado_animo || !genero_literatura) {
            return res.status(400).json({ message: 'Faltan parámetros.' });
        }

        if (username === "user" && password === "password") {
            const selectedValues = [String(edad), String(estado_animo), String(genero_literatura)];
            const prompt = createPrompt(selectedValues);
            const response = await sendPrompt(prompt);
            res.status(200).json({
                message: response,
                data: {
                    username,
                    edad: String(edad),
                    estado_animo: String(estado_animo),
                    genero_literatura: String(genero_literatura),
                }
            });
        } else {
            res.status(401).json({ message: 'Credenciales incorrectas.'});
        }
    } else {
        res.status(405).json({ message: 'Método no permitido.'});
    }
}