"use client";
import React from 'react';

export default function GeneratedPrompt({ generatedPrompt, promptFinished }) {
    return (
        <div className="p-2 flex flex-col items-center justify-center min-h-screen">
            <div className="p-4">
            {generatedPrompt ? (
                <div className="p-4 border border-gray-300 rounded bg-gray-50 max-w-xl w-full">
                    <h5 className="font-playwrite text-3xl mb-4 font-bold text-center">Tu <span className="text-bright-purple hover:text-dark-purple">historia</span></h5>
                    <p>{promptFinished}</p>
                </div>
            ) : (
                <div className="flex flex-col items-center justify-center">
                    <h1 className="text-3xl m-1 font-playwrite text-center">
                        Crea tu propia <span className="text-bright-purple hover:text-dark-purple">historia</span>
                    </h1>
                    <div className="m-4 border border-gray-300 rounded-xl bg-gray-50 max-w-xl w-full text-center">
                        <h5 className="p-4 font-bold">Por favor selecciona una opción en cada filtro.</h5>
                    </div>
                </div>
            )}
            </div>
        </div>

    );
}
