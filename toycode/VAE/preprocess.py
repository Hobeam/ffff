import torch
import torch.nn as nn
import torchaudio
import librosa

class MelSpectrogramConfig:
    sr: int = 22050
    win_length: int = 1024
    hop_length: int = 256
    n_fft: int = 1024
    f_min: int = 0
    f_max: int = 8000
    n_mels: int = 501
    power: float = 1.0
    pad_value: float = -11.5129251


class MelSpectrogram(nn.Module):

    def __init__(self, config: MelSpectrogramConfig):
        super(MelSpectrogram, self).__init__()

        self.config = config

        self.mel_spectrogram = torchaudio.transforms.MelSpectrogram(
            sample_rate=config.sr,
            win_length=config.win_length,
            hop_length=config.hop_length,
            n_fft=config.n_fft,
            f_min=config.f_min,
            f_max=config.f_max,
            n_mels=config.n_mels
        )

        self.mel_spectrogram.spectrogram.power = config.power

        mel_basis = librosa.filters.mel(
            sr=config.sr,
            n_fft=config.n_fft,
            n_mels=config.n_mels,
            fmin=config.f_min,
            fmax=config.f_max
        ).T
        self.mel_spectrogram.mel_scale.fb.copy_(torch.tensor(mel_basis))

    def forward(self, audio: torch.Tensor) -> torch.Tensor:
        """
        :param audio: Expected shape is [B, T]
        :return: Shape is [B, n_mels, T']
        """
        mel = self.mel_spectrogram(audio) \
            .clamp_(min=1e-5) \
            .log_()

        return mel

if __name__ == "__main__":        
    import torch
    import torchaudio
    from matplotlib import pyplot as plt
    from tqdm import tqdm
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
    featurizer = MelSpectrogram(MelSpectrogramConfig()).to(device)


    for idx in tqdm(range(2871)):
        wav, sr = torchaudio.load("/workspace/softwarecomputing/total/{}.wav".format(idx))
        wav = wav.to(device)

        mel_spectrogram = featurizer(wav)
        # print(wav.shape)
        # print(mel_spectrogram.shape)
        plt.imsave('mel-image/{}.png'.format(idx),mel_spectrogram.reshape((501,501)).cpu())
