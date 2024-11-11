import { useState, useEffect } from "react";
import { useRouter } from "next/router";

export default function Login() {
    const router = useRouter();
    const [user, setUser] = useState('');
    const [password, setPassword] = useState('');

    const handleLogin = async (e) => {
        e.preventDefault();
        if (user === "user" && password === "password") {
            router.push('/app');
        } else {
            alert('Credenciales incorrectas');
        }
    };

    return (
        <div className="login-container">
            <h1>Iniciar Sesión</h1>
            <form onSubmit={handleLogin}>
                <div>
                    <label>Usuario</label>
                    <input
                        type="text"
                        value={text}
                        onChange={(e) => setUser(e.target.value)}
                    />
                </div>
                <div>
                    <label>Contraseña</label>
                    <input
                        type="password"
                        value={password}
                        onChange={(e) => setPassword(e.target.value)}
                    />
                </div>
            </form>
        </div>
    );
}
